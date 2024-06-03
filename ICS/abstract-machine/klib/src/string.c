#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t cnt = 0;
  while(*s != '\0'){
    cnt ++;
    s++;
  }
  return cnt;
}

char *strcpy(char *dst, const char *src) {
  char *ret = dst;
  while((*dst++ = *src++) != '\0');
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  char *ret = dst;
  while(n-- > 0 && (*dst++ = *src++) != '\0');
  while(n-- > 0) *dst++ = '\0';
  return ret;
}

char *strcat(char *dst, const char *src) {
  char *ret = dst;
  while(*dst) dst++;
  while((*dst++ = *src++) != '\0');
  return ret;
}

char *strncat(char *dst, const char *src, size_t n) {
  char *ret = dst;
  while(*dst) dst++;
  while(n-- > 0 && (*dst++ = *src++) != '\0');
  *dst = '\0';
  return ret;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 && *s2 && *s1 == *s2){
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  while(n-- > 0 && *s1 && *s2 && *s1 == *s2){
    s1++;
    s2++;
  }
  if(n == 0) return 0;
  return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *s, int c, size_t n) {
  unsigned char *p = s;
  while(n-- > 0){
    *p++ = (unsigned char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  unsigned char *pdst = dst;
  const unsigned char *psrc = src;
  if(pdst < psrc){
    while(n-- > 0){
      *pdst++ = *psrc++;
    }
  } else {
    pdst += n;
    psrc += n;
    while(n-- > 0){
      *--pdst = *--psrc;
    }
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *pout = out;
  const unsigned char *pin = in;
  while(n-- > 0){
    *pout++ = *pin++;
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1, *p2 = s2;
  while(n-- > 0){
    if(*p1 != *p2){
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

#endif


