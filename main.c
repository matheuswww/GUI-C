asm(
  ".code16gcc\n"
  "call main\n"
  "call exit\n"
);
#include <assembly.h>
#include <shapes.h>
#include <bmp.h>
#include <omnistd.h> 

void *heaptr, *heapsaved;
extern boolean videoinit;
extern rgb **globalColors;

void main() {
  bitmap *bm;
  boolean ret;
  
  videoinit = false;
  globalColors = (rgb **)0; 

  freeall();
  videomode(x640x480x16);
  globalColors = setpalettes();
  if (!globalColors)
    return; 

  bm = parsebmp($1 "penguin", 5, 5);
  if (!bm) {
    print($1 "error\n\r");
    freeall();
    return;
  }

  ret = drawbmp(bm);


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
  int16 newsize;

  if(!size)
    return $v 0;

  newsize = ((heaptr-heap1)+size);
  if (newsize > heapsz)
    return $v 0;

  p = heaptr;
  heaptr += size;

  return p;
}

void freeall() {
  heaptr = heap1;

  return;
}

void save(void) {
  heapsaved = heaptr;

  return;
}

void load() {
    heaptr = heapsaved;

    return;
}

int16 open(int8 *file, int16 offset) {
  int16 fd, ret;

  fd = xopen(file);
  if (!fd)
    return 0;

  ret = xmove(fd, offset);
  if (!ret) {
    close(fd);
    return 0;
  }
  
  return fd;
}

int8 read(int16 fd) {
  int16 n;
  int8 ah, al;

  n = xread(fd);
  al = (n & 0xff);
  ah = ((n & 0xff00) >> 8);
  if (ah) {
    printf("xread() error code = 0x%\n", $2 al);
    return (int8)0;
  }
  return al;
}

void close(int16 fd) {
  xclose(fd);
}