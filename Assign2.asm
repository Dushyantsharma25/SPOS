section .data
    result db "Result: %d", 10, 0
    num1   db 5
    num2   db 3

section .bss
    res resb 4

section .text
    global _start

%macro Addition 2
    mov al, %1
    add al, %2
    mov [res], al
%endmacro

%macro Subtract 2
    mov al, %1
    sub al, %2
    mov [res], al
%endmacro

%macro Multiply 2
    mov al, %1
    imul al, %2
    mov [res], al
%endmacro

%macro Division 2
    mov al, %1
    mov bl, %2
    div bl
    mov [res], al
%endmacro

_start:
    Addition num1, num2
    Subtract num1, num2
    Multiply num1, num2
    Division num1, num2

    mov eax, 1
    xor ebx, ebx
    int 0x80

