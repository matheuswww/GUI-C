#pragma once
#include "gui.h"
#include "assembly.h"

#define MaxX        640
#define MaxY        480
#define x40x25xT    0x00
#define x640x480x16 0x12

#define FlagNone 0x00
#define FlagSolid 0x01

struct s_point {
  int16 x;
  int16 y;
  int8 color:4;
} packed;
typedef struct s_point point;

struct s_line {
  point *p1;
  point *p2;
  int8 color:4;
  int16 thickness;
} packed;
typedef struct s_line line;

struct s_rectangle {
  point *p1;
  point *p2;
  int8 fgcolor:4;
  int16 bgcolor:8;
  int8 color:4;
  boolean solid:1;
  int16 thickness;
  int8 flags:4;
} packed;
typedef struct s_rectangle rectangle;

struct s_rgb {
  int8 red;
  int8 green;
  int8 blue;
  int8 _;
} packed;
typedef struct s_rgb rgb;

typedef rgb colortable[16];

rgb **setpalettes();
void setpalette(int8,rgb*);
void videomode(int8);
int16 getmaxx(void);
int16 getmaxy(void);
boolean drawpoint(point*);
boolean drawline(line*);
boolean drawrectangle(rectangle*);

point *mkpoint(int16,int16,int8);
line *mkline(point*,point*,int8,int16);
rectangle *mkrectangle(point *pnt1, point *pnt2, int8 fgcolor, int8 bgcolor, int16 thickness, boolean solid);
rgb *mkrgb(int8,int8,int8);