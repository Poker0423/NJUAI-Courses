#include "asm.h"

int64_t asm_add(int64_t a, int64_t b) {
  int64_t result = 0;
  __asm__(
  "movq %1, %0;"\
  "addq %2, %0":
  "=r" (result):
  "m" (a), "m" (b)
  );
  return result;
}

int asm_popcnt(uint64_t x) {
  uint64_t s = 0;
  uint64_t c1 = 0x5555555555555555, c2 = 0x3333333333333333, c3 = 0x0F0F0F0F0F0F0F0F, 
    c4 = 0x00FF00FF00FF00FF, c5 = 0x0000FFFF0000FFFF, c6 = 0x00000000FFFFFFFF;
  //有效在%0中
  __asm__(
  "movq %2, %0;"\
  "shrq $1, %2;"\
  "andq %3, %2;"\
  "andq %3, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;"\

  "shrq $2, %2;"\
  "andq %4, %2;"\
  "andq %4, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;"\

  "shrq $4 ,%2;"\
  "andq %5, %2;"\
  "andq %5, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;"\

  "shrq $8, %2;"\
  "andq %6, %2;"\
  "andq %6, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;"\

  "shrq $16, %2;"\
  "andq %7, %2;"\
  "andq %7, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;"\

  "shrq $32, %2;"\
  "andq %8, %2;"\
  "andq %8, %0;"\
  "addq %2, %0;"\
  "movq %0, %2;":
  "=r" (s):
  "0" (s), "r" (x), "m"(c1), "m"(c2), "m"(c3), "m"(c4), "m"(c5), "m"(c6)
  );

  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  __asm__(
    "mov $0, %%rsi;"\
    "1:;"\
    "movb (%0, %%rsi), %%al;"\
    "movb %%al, (%1, %%rsi);"\
    "inc %%rsi;"\
    "cmp %%rsi, %2;"\
    "jg 1b":
    :
    "r"(src), "r"(dest), "r"(n):
    "memory", "rsi", "rax"
  );
  
  return dest;
}


//asm_jmp_buf的类型
typedef struct {
  void *rbp, *rbx, *rip, *rsp, *r10, *r13, *r14, *r15;
} asm_jmp_buf;

int asm_setjmp(asm_jmp_buf *env) {
  __asm__ volatile(
    // 存rbx
    "movq %%rbx, 8(%0);"\
    // 存 r10, r13 - r15
    "movq %%r10, 32(%0);"\
    "movq %%r13, 40(%0);"\
    "movq %%r14, 48(%0);"\
    "movq %%r15, 56(%0);"\
    //恢复
    // 存old rip
    "movq (%%rsp), %%rax;"\
    "movq %%rax, 16(%0);"\
    // 存saved rpb
    "movq %%rbp, 0(%0);"\
    // 存last rsp
    "lea 8(%%rsp), %%rax;"\
    "mov %%rax, 24(%0);"\
    "xorq %%rax, %%rax;"
    : /* no output */
    : "D"(env) /* input */
    : "memory", "cc", "%rax" /* clobbered */
  );
  
  return 0;
}

void asm_longjmp(asm_jmp_buf *env, int val) {
  __asm__ volatile(
    // 恢复saved rbp
    "movq 0(%0), %%rbp;"\
    // 恢复rbx
    "movq 8(%0), %%rbx;"\
    // 恢复r10, r13-r15
    "movq 32(%0), %%r10;"\
    "movq 40(%0), %%r13;"\
    "movq 48(%0), %%r14;"\
    "movq 56(%0), %%r15;"\
    // 取rip
    "movq 16(%0), %%rcx;"\
    /* 如果是0，就加1 */
    "testl	%%eax, %%eax;"\
    "jnz	1f;"\
    "inc	%%eax;"\
    "1:movq 24(%0), %%rsp;"\
    //恢复rip
    "jmp *%%rcx;"
    : /* no output */
    : "D"(env), "S"(val) /* input */
    : "memory", "cc", "%rcx" /* clobbered */
  );
}

