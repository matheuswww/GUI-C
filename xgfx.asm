bits 16
%include "xgfx.h"
global heap1
global heapsz
global exit
global xputchar
global heap1
global xvideomode
global xgetchar
global xdrawpointT
global xdrawpoint
global xopen
global xclose
global xmove
global xread
global xsetpalette

heap1  dd _heap
_heap: 
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
      times 0x1000 db 0x00
heapsz: dw ($-_heap)

xsetpalette:
  push bp
  mov bp,sp

  mov ax, 0x1010
  arg bx,0
  xor cx,cx
  xor dx,dx
  arg ch,2
  arg cl,3
  arg dh,1
  int 0x10

  mov sp,bp
  pop bp
  ret

xopen:
    push bp
    mov bp,sp

    mov ax,0x3d00
    arg dx,0
    clc
    int 0x21

    jc .error
    jmp .end

  .error:
    neg ax
  .end:
    mov sp,bp
    pop bp
    ret

xmove: 
    push bp
    mov bp, sp

    mov ax, 0x4200
    arg bx,0
    xor cx,cx
    arg dx,1

    clc
    int 0x21

    jc .error
    mov ax,0x01
    jmp .end

  .error:
    xor ax,ax
  .end:
    mov sp,bp
    pop bp
    ret

xclose:
    push bp
    mov bp,sp

    mov ax,0x3e00
    arg bx,0
    clc
    int 0x21

    jc .error
    mov ax,0x01
    jmp .end
  
  .error:
    xor ax,ax
  .end:
    mov sp,bp
    pop bp
    ret

readbuf db 0x00

xread:
    push bp
    mov bp,sp

    mov ax,0x3f00
    arg bx,0
    mov cx,0x01
    mov dx,readbuf

    clc
    int 0x21
    jc .error

    mov bx,readbuf
    xor ax,ax
    mov byte al,[bx]
    jmp .end

  .error:
    mov ah,0xff
  .end:
    mov sp,bp
    pop bp
    ret

xdrawpoint:
  push bp
  mov bp,sp

  arg cx,0
  arg dx,1
  arg ax,2

  xor bx,bx
  mov ah,0x0c
  int 0x10

  mov sp,bp
  pop bp
  ret

xdrawpointT:
  push bp
  mov bp, sp

  arg ax,0
  arg dx,1

  and dx,0xf
  and ax,0xf
  mov dh,al

  xor ax,ax
  mov ah,0x02
  xor bx,bx
  int 0x10

  mov ah,0x0a
  mov al,'+'
  xor bx,bx
  mov cx,0x01
  int 0x10

  mov ax,0x01
  mov sp,bp
  pop bp
  ret

xgetchar:
  push bp
  mov bp,sp

  xor ax,ax
  int 0x16

  mov sp,bp
  pop bp
  ret

xvideomode:
  push bp
  mov bp,sp

  arg ax,0
  xor ah,ah
  int 0x10

  mov sp,bp
  pop bp
  ret

exit:
  push bp
  mov bp, sp

  xor ax,ax
  int 0x21

.halt:
  cli
  hlt
  jmp .halt 

  mov sp,bp
  pop bp
  ret

xputchar:
  push bp
  mov bp,sp

  arg ax,0
  mov ah,0x0e
  xor bx,bx
  int 0x10

  mov sp,bp
  pop bp
  
  ret