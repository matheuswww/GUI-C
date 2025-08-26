#pragma once
#include "gui.h"
#include "assembly.h"

#define MaxX     40
#define MaxY     25
#define x40x25xT 0

struct s_point {
  int16 x;
  int16 y;
  int8 color:4;
} packed;
typedef struct s_point point;

void videomode(int8);
int8 getmaxx(void);
int8 getmaxy(void);
boolean drawpoint(point*);

point *mkpoint(int16,int16);