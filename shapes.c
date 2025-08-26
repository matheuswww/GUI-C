#include "./include/gui.h"
#include "./include/assembly.h"
#include "./include/shapes.h"

boolean videoinit;

point *mkpoint(int16 x,int16 y) {
  point *p;
  int16 size;

  size = sizeof(struct s_point);
  p = alloc(size);
  if (!p)
    return (point *)0;

  p->x = x;
  p->y = y;

  return p;
}

void videomode(int8 mode) {
  if (mode > 0x9f)
    return;
  
  xvideomode(mode);
  videoinit = true;

  return;
}

int8 getmaxx() {
  return (MaxX-1);
}

int8 getmaxy() {
  return (MaxY-1);
}

boolean drawpoint(point *pnt) {
  int16 maxx, maxy;

  if (!videoinit)
    return false;
  if (!pnt)
    return false;

  maxx = getmaxx();
  maxy = getmaxy();

  if ((pnt->x > maxx) || (pnt->y > maxy))
    return false;

  return xdrawpointT(pnt->x, pnt->y); 
} 