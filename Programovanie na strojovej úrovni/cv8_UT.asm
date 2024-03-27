%include "rw32-2020.inc"

section .data

    str1 db "ff0",0
    val1 dd 0
    
    strA db "@#$j Svete!",0
    strB db "           ",10

section .text

; pascal int isdigit(char c) {
;   return c >= '0' && c <= '9';
; }
;
; ESP+4 -> c
; ESP   -> EIP
isdigit:
    mov al,[esp+4]
    cmp al,'0'
    jl .false
    cmp al,'9'
    jg .false
    mov eax,1
    jmp .exit
.false:
    xor eax,eax    
.exit:   
    ret 4

; cdecl int atoi(const char *pStr, int base) {
;   if (base <= 1 & base > 35) return 0;
;   if (pStr == NULL) return 0;
;   int EAX = 0;
;   int ECX = 0;
;   while(pStr[ECX] != 0) {
;     char BL = pStr[ECX++];
;     if (isdigit(BL))
;       BL = BL - '0';
;     else if (BL >= 'A' && BL - 'A' + 10 < base) 
;       BL = BL - 'A' + 10;
;     else if (BL >= 'a' && BL - 'a' + 10 < base) 
;       BL = BL - 'a' + 10;
;     else
;       //return 0;
;       BL = 0;
;     EAX = EAX*base + (int)BL;
;   }
;   return EAX;
; }
;

; 1 < base <= 10

; +12   base
; +8    str1
; +4    EIP
;ESP -> stare EBP <- EBP

%define base ebp+12
%define pStr ebp+8

atoi:
    push ebp
    mov ebp,esp
;    sub esp,0
    xor eax,eax
    mov esi,[pStr]
    test esi,esi
    jz .exit    
    cmp [base],dword 1
    jle .exit
    cmp [base],dword 35
    jg .exit
    
    xor ecx,ecx
.while:
    movsx ebx,byte [esi+ecx] ; BL = pStr[ecx]
    test bl,bl       ; if (BL == 0) goto endwhile
    jz .endwhile
    inc ecx
    
    push eax
    push ebx
    call isdigit
    test eax,eax
    jnz .isdigit
    cmp bl,'A'
    jl .not_valid_digit        
    sub ebx,'A'
    add ebx,10
    cmp ebx,[base]
    jge .not_valid_digit
    jmp .endif
.isdigit:
    sub ebx,'0'
    jmp .endif
.not_valid_digit:    
    xor ebx,ebx
.endif:
    pop eax

    imul dword [base]
    add eax,ebx
    jmp .while
.endwhile:
.exit:  
;    mov esp,ebp
    pop ebp
    ret

; cdecl void toupper(const char *pSrc, char *pDest) {
; //cdecl char* toupper(const char *pSrc) {
; //cdecl void toupper(char *pSrc) {
;   int ecx = 0;
;   while (pSrc[ecx] != 0) { 
;     char al = pSrc[ecx];
;     if (al >= 'a' && al <= 'z') al = al & 0xDF; // 0110 0001 -> 0100 0001 A
;     pDest[ecx] = al;                            // 1101 1111
;     ecx++;
; }

; 'a' -> 'A'
; !pSrc || !pDest => return
; pSrc a pDest ... ASCIIZ = zakonceny 0

toupper:
    push ebp
    mov ebp,esp
    push esi
    push edi
    push eax
    
    mov esi,[ebp+8]  ; ... pSrc
    mov edi,[ebp+12] ; ... pDest
    test esi,esi
    jz .exit
    test edi,edi
    jz .exit    
;    xor ecx,ecx
.while:
    lodsb ; AL = *ESI, ESI++
    cmp al,0
    jz .endwile
    cmp al,'a'
    jb .nochange
    cmp al,'z'
    ja .nochange
    and al,1101_1111b
.nochange:
    stosb ; *EDI = AL, EDI++
    jmp .while       
.endwile:    
    stosb
.exit:
    pop eax
    pop edi
    pop esi
    pop ebp
    ret

; strlen, strstr, strreplace

CMAIN:
    push ebp
    mov ebp, esp
    
    push dword 16
    push str1
    call atoi
    add esp,8
    
    push strB
    push strA
    call toupper
    add esp,8

    pop ebp
    ret