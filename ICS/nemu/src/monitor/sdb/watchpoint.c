/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[128];
  uint32_t res;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static int nr_wp_used = 0;

bool new_wp(char *e) {
  if (nr_wp_used >= NR_WP) {
    return false;
  }
  
  WP *wp_to_add = free_;
  free_ = free_->next;

  if (head == NULL) {
    head = wp_to_add;
    head->next = NULL;
    strcpy(head->expr, e);
    wp_to_add->res = 0;
  } else {
    WP *itr = head;
    while (itr->next != NULL) {
      itr = itr->next;
    }
    itr->next = wp_to_add;
    wp_to_add->next = NULL;
    strcpy(wp_to_add->expr, e);
    wp_to_add->res = 0;
  }
  
  nr_wp_used++;
  return true;
}


void free_wp(int n) {
  if (nr_wp_used <= 0) return;

  WP* wp_to_free = NULL;
  WP* prev = NULL;
  WP* curr = head;

  while (curr != NULL) {
    if (curr->NO == n) {
      wp_to_free = curr;
      if (prev == NULL) {
        head = curr->next;
      } else {
        prev->next = curr->next;
      }
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  if (wp_to_free == NULL) return;

  wp_to_free->next = free_;
  free_ = wp_to_free;

  nr_wp_used--;
}

void traverse_wp(){
  WP *itr = head;
  while(itr != NULL){
    printf("%02d\t%10s\t%-10u\n",itr->NO,itr->expr,itr->res);
    itr = itr->next;
  }
}

word_t expr(char *e, bool *success);


void diff_check_wp() {
    bool has_print_head = false;
    for (WP *itr = head; itr != NULL; itr = itr->next) {
        bool success = false;
        uint32_t res = expr(itr->expr, &success);
        if (!success) {
            printf("The expression of watch point %d is invalid!\n", itr->NO);
        } else if (res != itr->res) {
            if (!has_print_head) {
                printf("%-6s\t%-20s\t%-14s\t%-14s\n", "Number", "Expression", "New Value", "Old Value");
                has_print_head = true;
            }
            printf("%-6d\t%-20s\t%-14u\t%-14u\n", itr->NO, itr->expr, res, itr->res);
            itr->res = res;
            nemu_state.state = NEMU_STOP;
        }
    }
}

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

