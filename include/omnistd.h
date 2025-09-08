#pragma once
#include <gui.h>

#define BufSz 256

#define printf(f,args...) do {          \
  int8 _tmp[BufSz];                      \
  zero(_tmp, BufSz);                    \
  snprintf(_tmp, (BufSz-1), f, args);   \
  print(_tmp);                          \
} while(false);
#define min(x, y)             ((x) < (y)) ? (x) : (y)
#define zero(x, y)            set((x), 0, (y))
#define copy(d, s, z)         memorycopy(d, s, z, false)
#define stringcopy(d, s, z)   memorycopy(d, s, z, true)
#define overflow(x)           if (bytes > (min(BufSz,size)-(x))) {  \
  continuation = false;                                           \
  break;                                                          \
}

void memorycopy(int8*,int8*,int16, boolean);
void set(int8*,int8,int16);
int8 *snprintf(int8*,int16,int8*, ...);
int8 *int2hex(int16);
int16 stringlen(int8 *str);
int8 hexchar(int8);