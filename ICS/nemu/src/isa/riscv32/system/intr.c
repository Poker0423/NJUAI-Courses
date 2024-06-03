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
enum
{
  mepc = 0,
  mstatus = 1,
  mcause = 2,
  mtvec = 3
};
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
    #ifdef CONFIG_ETRACE_DEBUG
  Log("etrace: ecall %d",NO);
  #endif
  cpu.csr[mcause] = NO;
  cpu.csr[mepc] = epc + 4; // 下一条不是ecall而是ecall+4
  return cpu.csr[mtvec];
}
/*中断返回 mret*/
word_t isa_exit_intr()
{
  IFDEF(CONFIG_ETRACE_DEBUG, Log("etrace: mret"));

  return cpu.csr[mepc];
}
word_t isa_query_intr() {
  return INTR_EMPTY;
}