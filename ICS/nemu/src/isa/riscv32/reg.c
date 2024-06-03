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

#include <isa.h>
#include "local-include/reg.h"

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
    int length =  sizeof(regs) / sizeof(regs[0]);
    for(int i = 0  ; i < length ; i ++)
        printf("reg$%s ---> %d\n",regs[i], cpu.gpr[i]);
}


word_t isa_reg_str2val(const char *s, bool *success) {
    char *newRegs[32];
    for (int i = 0; i < 32; i++) {
        int len = strlen(regs[i]);
        char *newReg = malloc(len + 2); // 加上$符号的长度为原长度+1
        strcpy(newReg, "$");
        strcat(newReg, regs[i]);
        newRegs[i] = newReg;
    }
    for (int j = 0; j < 32; j++) {
      if (strcmp(s, newRegs[j]) == 0) {
        return cpu.gpr[j];
      }
    }
  //printf("%d\n",32);
  return 0;
}
