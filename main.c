asm(
  ".code16gcc\n"
  "call main\n"
  "call exit\n"
);
#include <gui.h>
#include <assembly.h>
#include <shapes.h>

void *heaptr;
extern boolean videoinit;

void main() {
  point *pnt1, *pnt2, *pnt3;

  videoinit = false;
  freeall();

  videomode(x40x25xT);
  pnt1 = mkpoint(10, 6);
  pnt2 = mkpoint(9, 15);
  pnt3 = mkpoint(1, 3);
  if (!pnt1 || !pnt2 || !pnt3)
    print($1 "Memory error \r\n");
  drawpoint(pnt1);
  drawpoint(pnt2);
  drawpoint(pnt3);
  getchar();

  freeall();
  return;
}

int8 getchar(void) {
  int8 al, ah, ax;
  int8 ret;

  ax = xgetchar();
  al = (ax & 0xf);
  ah = ((ax & 0xf0) >> 4);

  ret = (al) ? al : ah;

  return ret;
}

void putchar(int8 c) {
  xputchar(c);

  return;
}

void print(int8 *str) {
  int8 *p;

  for (p=str; *p; p++)
    putchar(*p);

  return;
}

void *alloc(int16 size) {
  void *p;

  if(!size)
    return $v 0;

  p = heaptr;
  heaptr += size;

  return p;
}

void freeall() {
  heaptr = heap1;

  return;
}