bits 16
%include "xgfx.h"
global exit

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