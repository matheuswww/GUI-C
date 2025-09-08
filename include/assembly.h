/* assembly.h */
#pragma once
#include "gui.h"

void xputchar(int8);
void xvideomode(int8);
int8 xgetchar(void);
boolean xdrawpointT(int16, int16);
boolean xdrawpoint(int16, int16, int8);

int16 xopen(int8*);
boolean xmove(int16,int16);
boolean xread(int16);
boolean xclose(int16);
void xsetpalette(int16,int8,int8,int8);
void xsetpalettes(void);