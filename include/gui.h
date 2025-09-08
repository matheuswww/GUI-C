/* gui.h */
#pragma once

#define $1 (int8 *)
#define $2 (int16)
#define $v (void *)
#define false 0
#define true 1

#define packed __attribute__((packed))

#define zero(x, y) set((x), 0, (y))

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int boolean;

extern void *heap1;
extern int16 heapsz;

void print(int8*);
void putchar(int8);
void *alloc(int16);
void freeall(void);
void save(void);
void load(void);
void videomode(int8);
int8 getchar(void);
int16 open(int8*, int16);
int8 read(int16);
void close(int16);
int16 stringlen(int8*);