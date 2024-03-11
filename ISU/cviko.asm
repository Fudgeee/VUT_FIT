%include "rw32-2018.inc"

section .data
    vala dd 2.0
    valc dd 5.5
    valv dd 4.0
    ;dva dd 2.0
    tri dd 3.0
    styri dd 4.0
    
section .text
objem_gule:
    enter 0,0
    finit
    fld dword [styri]
    fld dword [tri]
    fdivp st1,st0
    fldpi
    fmulp st1
    fld dword [r]
    fmul st0
    fld dword [r]
    fmulp st1
    fmulp st1
    leave
    ret

obsah_lichobezniku:
;   cdecl double obsah_lichobezniku(float a, float c)
;   S = ((a+c)/2)*v
%define a ebp+8
%define c ebp+12
%define v ebp+16
    enter 0,0
    finit
    fld dword [a] ; a
    fadd dword [c] ; a+c
    ;fld dword [dva] ; 2 a+c
    fld1
    fadd st0,st0
    fdivp st1,st0 ; (a+c)/2
    fmul dword [v] 
    
    leave
    ret
_main:
    push ebp
    mov ebp, esp
    
    
;    finit
;    fld dword [a]
;    fmul st0
;    call WriteDouble
;    call WriteNewLine
    
;    fst dword [S]
;    mov eax,[S]
;    call WriteDouble
;    call WriteNewLine
;    push dword [valv]
;    push dword [valc]
;    push dword [vala]
;    call obsah_lichobezniku
;    add esp,12
    call objem_gule
    call WriteDouble
    call WriteNewLine 
    pop ebp
    ret