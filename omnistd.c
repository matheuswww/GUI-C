#include <omnistd.h>
#include <gui.h>

void memorycopy(int8 *dst, int8 *src, int16 size, boolean str) {
  int16 n;
  int8 *dptr, *sptr;

  for (n=size, dptr=dst, sptr=src; (str && *sptr) &&  n; n--, dptr++, sptr++)
    *dptr = *sptr;

  if (str) {
    dptr++;
    *dptr = 0;
  }

  return;
}

void set(int8 *dst, int8 c, int16 size) {
  int16 n;
  int8 *p;

  for (p=dst, n=size; n--; p++)
    *p = c;

  return;
}

int8 hexchar(int8 c) {
  if (c < 10)
    return (c+'0');
  else if (c > 9)
    return ((c-10)+'a');
  else
    return 'x';
}

int8 *int2hex(int16 val) {
  int8 a, b, c, d;
  int8 a_, b_, c_, d_;
  int8 *ret;

  d_ = (val & 0x000f);
  c_ = ((val & 0x00f0) >> 4);
  b_ = ((val & 0x0f00) >> 8);
  a_ = ((val & 0x0f000) >> 12);

  a = hexchar(a_);
  b = hexchar(b_);
  c = hexchar(c_);
  d = hexchar(d_);

  ret = $1 alloc(5);
  ret[0] = a;
  ret[1] = b;
  ret[2] = c;
  ret[3] = d;
  ret[4] = 0;

  return ret;
}

int16 stringlen(int8 *str) {
  int16 n;
  int8 *p;

  if (!str)
    return 0;

  for (p=str, n=0; *p; p++, n++);

  return n;
}

int8 *snprintf(int8 *dst, int16 size, int8 *fmt, ...) {
  int8 *dptr, *sptr, *p;
  int8 **pptr;
  int8 buf[BufSz];
  int16 bytes, argc, len;
  int16 *ip;
  boolean continuation;
  void *mem;

  if (!dst || !fmt)
    return $1 0;

  pptr = &fmt;
  zero($1 &buf, BufSz);
  bytes = argc = 0;
  sptr = fmt;
  dptr = dst;
  continuation = true;

  while (*sptr && continuation) {
    switch (*sptr)
    {
    case '%':
      overflow(2);
      sptr++;
      switch (*sptr)
      {
        case 0:
          break;
        case 'c':
          overflow(2);
          p = *++pptr;
          mem = (void *)p;
          *dptr++ = (int8)mem;
          bytes++;
          sptr++;
          break;
        case 's':
          p = *++pptr;
          len = stringlen(p);
          if (len) {
            overflow((len+1));
            stringcopy($1 dptr, $1 p, len);
            dptr += len;
            bytes+=len;
          }
          sptr++;
          break;
        case 'x':
          overflow(5);
          p = *++pptr;
          mem = (void *)p;
          ip = (int16 *)mem;
          p = int2hex(*ip);

          stringcopy($1 dptr, $1 p, 4);
          dptr += 4;
          bytes += len;
          sptr++;
          break;

        case '%':
          overflow(2)
          *dptr++ = '%';
          sptr++;
          bytes++;
          break;
        break;
      }
      break;
    
    case '\n':
      overflow(3)
      *dptr = '\r';
      *dptr = '\n';
      sptr++;
      bytes+=2;
      break;

    default:
      overflow(2)
      *dptr++ = *sptr++;
      bytes++;
      break;
    }
  }
  *dptr = 0;

  return dst;
} 