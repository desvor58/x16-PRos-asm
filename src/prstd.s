[BITS 16]

%macro DEF_C_FUN 1
    section .text.%1
    global %1
    %1:
        push bp
        mov bp, sp
%endmacro

%macro C_FUN_END 0
    pop bp
    ret
%endmacro

section .bss
global args
args: resw 1

section .text.cstart
global _cstart

extern main
_cstart:
    mov [args], si
    call main
    retf


DEF_C_FUN putchar
    mov al, [bp + 4]
    mov ah, 0x0E
    int 0x10
C_FUN_END

DEF_C_FUN puts
    push bx
    push si

    mov ah, 0x01
    mov si, [bp + 4]
    int 0x21

    mov ax, 0x0E0A
    mov bx, 0x0F
    int 0x10
    mov al, 0x0D
    int 0x10

    pop si
    pop bx
C_FUN_END

DEF_C_FUN far_puts
    push bx
    push si
    push ds

    mov si, [bp + 4]
    mov ds, [bp + 6]

    mov ah, 0x0E
    mov bx, 0x0F
.put_loop:
    mov al, [si]
    test al, al
    jz .put_done
    int 0x10
    inc si
    jmp .put_loop

.put_done:
    pop ds
    pop si
    pop bx
C_FUN_END

DEF_C_FUN prints
    push si

    mov ah, 0x01
    mov si, [bp + 4]
    int 0x21

    pop si
C_FUN_END

DEF_C_FUN far_prints
    push si
    push ds

    mov si, [bp + 4]
    mov ds, [bp + 6]

    mov ah, 0x0E
    mov bx, 0x0F
.put_loop:
    mov al, [si]
    test al, al
    jz .put_done
    int 0x10
    jmp .put_loop

.put_done:
    pop si
    pop ds
C_FUN_END

DEF_C_FUN load_file
    push si
    push bx
    push cx
    
    mov ah, 0x02
    mov cx, [bp + 4]
    mov si, [bp + 6]
    int 0x22
    mov ax, bx

    pop cx
    pop bx
    pop si
C_FUN_END

DEF_C_FUN load_huge_file
    push si
    push bx
    push cx
    
    mov ah, 0x10
    mov dx, [bp + 6]
    mov cx, [bp + 8]
    mov si, [bp + 10]
    int 0x22
    sbb ax, ax

    pop cx
    pop bx
    pop si
C_FUN_END
