#pragma once
#include <gui.h>
#include <shapes.h>

#define BmpHdrSz 118

struct s_bitmapheader {
  int16 signature;
  int16 __, ___;
  int16 ____, _____;
  int16 offset, ______;
};
typedef struct s_bitmapheader bitmapheader;

struct s_infoheader {
  int16 _, __;
  int16 width, ___;
  int16 height, ____;
  int16 _____;
  int16 ______;
  int16 _______, ________;
  int16 _________, ___________;
  int16 ____________, _____________;
  int16 ______________, _______________;
  int16 ________________, _________________;
  int16 __________________, ___________________;
};
typedef struct s_infoheader infoheader;

  

struct s_bitmap {
  int8* filename;
  int16 x;
  int16 y;
  bitmapheader *hdr;
  infoheader *info;
  colortable *colors;
} packed;
typedef struct s_bitmap bitmap;

bitmap* parsebmp(int8*,int16,int16);
boolean drawbmp(bitmap*);
int8 *addbmp(int8 *);
int8 getclr(colortable *colors, int8 input);