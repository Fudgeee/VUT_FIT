%include "rw32-2020.inc"

section .data

    str1     db "Ahoj Ahoj"
    str2     db "---------"
    str3     db "Ahoj-----"
    str1_len dd 9
    str2_len dd 9
    str3_len dd 9
    
    arr1     dw 0,5,-6,10,-6
    arr2     dd 0,0,0,0,0

section .text

; void arrcpy(const long* src, long* dest, int N) ...
;     rep movsd ; ESI += 4, EDI +=4 a ECX--

; void strncpy(const char* src, char* dest, int N) {
;   if (src != NULL && dest != NULL) {
;     for(;N>0;N--) dest[N - 1] = src[N - 1];
;   }
; }
;
; tato funkce meni obsah ECX
; ECX = N
; ESI = src
; EDI = dest
;
strncpy:
    push ecx
    push esi
    push edi
    
    test esi,edi ; EDI & ESI
    jz .endfor
    cmp ecx,0
    jle .endfor

    rep movsb ; meni ESI, EDI a ECX
    
.endfor:
    pop edi
    pop esi
    pop ecx
    ret

; int strncmp(const char* s1, const char* s2, int N) {
;   if (s1 != NULL && s2 != NULL) {
;     for(;N>0;N--) if (s1[N - 1] != s2[N - 1]) 
;       return 0;
;     return 1;
;   }
;   return 0;
; }
;
; EAX - vysledek
strncmp:
    push ecx
    push esi
    push edi

    xor eax,eax
    test esi,edi ; EDI & ESI
    jz .endfor
    cmp ecx,0
    jle .endfor
    
    repz cmpsb ; do { ecx--; ZF = (byte [esi] == [edi]); } while (ZF && ECX != 0)
    test ecx,ecx
    jnz .endfor
    inc eax
    
.endfor:        
    pop edi
    pop esi
    pop ecx
    ret

; int find_char(char a, const char* s, int N) {
;   if (s != NULL) {
;     for(int i=0;i<N;i++) if (s[i] == a) return 1;
;   }
;   return 0;
; }
;
; EDI = *s
; AL  =  a
; ECX =  N
;
; SCASB ... ZF = (AL == [EDI]), EDI++
find_char:
    push ecx
    push edi
    push ebx

    xor ebx,ebx
    test edi,edi ; EDI & ESI
    jz .endfor
    cmp ecx,0
    jle .endfor
    
    repnz scasb
    test ecx,ecx
    jz .endfor
    inc ebx
    
.endfor:
    mov eax,ebx
      
    pop ebx    
    pop edi
    pop ecx
    ret

find_char_pos:
    push edi
    push ecx
    push ecx

    xor ebx,ebx
    test edi,edi ; EDI & ESI
    jz .endfor
    cmp ecx,0
    jle .endfor
    
    cld ; std
    repnz scasb
    test ecx,ecx
    jz .endfor
    pop eax
    sub eax,ecx
    dec eax
    jmp .exit
.endfor:
    mov eax,-1
    add esp,4
.exit:      
    pop ecx
    pop edi
    ret
        
; int count_w(short v, const short* pArray, int N) {
;   return pocet vyskytu hodnot 'v' v poli 'pArray'
; }
;
; AX  =  v
; EDI = *pArray
; ECX =  N
;
count_w:
    push ecx
    push edi
    push ebx

    xor ebx,ebx
    test edi,edi 
    jz .exit

.while:
    cmp ecx,0
    jle .exit
    scasw ; cmp ax,[edi], edi += 2
    jnz .not_same
    inc ebx
.not_same:
    dec ecx
    jmp .while
        
.exit:
    mov eax,ebx
      
    pop ebx    
    pop edi
    pop ecx
    ret
            
CMAIN:
    push ebp
    mov ebp, esp
    
    mov ecx,[str1_len]
    mov esi,str1
    mov edi,str1
    call strncmp
    
    mov al,'o'
    mov ecx,9
    mov edi,str1
    call find_char_pos
    
    mov ax,-6
    mov ecx,5
    mov edi,arr1
    call count_w

    mov ax,-6
    mov ecx,5
    mov edi,0
    call count_w
    
    mov ax,-6
    mov ecx,0
    mov edi,arr1
    call count_w
    
    mov ax,-6
    mov ecx,-100
    mov edi,arr1
    call count_w    
    
    mov ax,1000
    mov ecx,5
    mov edi,arr1
    call count_w
    
    mov ax,0
    mov ecx,5
    mov edi,arr1
    call count_w    
        
    pop ebp
    ret