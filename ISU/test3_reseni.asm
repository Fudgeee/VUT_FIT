%include "rw32-2018.inc"

section .data    
        string db "300",0
       
section .text
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp,esp
    
    mov esi,string
    mov ebx,19    
    call task31
    
    push __float32__(8.0)
    push __float32__(-64.0)    
    call task32
    add esp,8

    mov esp,ebp
    pop ebp
    ret    
;
;--- Úkol 1 --- 
;
; Naprogramujte funkci, která převede řetězec na číselnou hodnotu. Registr ESI ukazuje 
; na řetězec, který reprezentuje 32bitové celé číslo bez znaménka v číselné soustavě  
; dané registrem EBX. Výsledné číslo uložte do registru EAX. 
;
; K řešení tohoto problému můžete (nemusíte) využít funkci jazyka C:
;
;   unsigned long int strtoul(const char *str, char **endptr, int base),
;
; která vrací 32bitovou hodnotu bez znaménka získanou převodem textové 
; reprezentace čísla v soustavě "base" uloženého na adrese "str".
; Ukazatel "endptr" není pro naše účely potřeba a lze ho nastavit na 0. 
;
; Ukázka návrhu řešení v jazyce C:
;
;   EAX = strtoul(ESI, 0, EBX);
;
; Vstup:
;   EBX = základ číselné soustavy, ze které se budou čísla převádět
;   ESI = ukazatel na řetězec reprezentující číslo 
;
; Výstup:
;   EAX = číslo převedené z textové reprezentace
;
; Důležité:
;   Funkce musí zachovat obsah všech registrů kromě EAX a příznakového registru.
;   Zásobníkový rámec není potřeba.
;   Funkce "strtoul" mění obsah některých registrů (např. ECX, EDX ...).
;
; Hodnocení: až 1 bod.
; 
task31:
    push ecx
    push edx
    
    push ebx
    push 0
    push esi
    call strtoul
    add esp, 12
    
    pop edx
    pop ecx
    ret
;
;--- Úkol 2 ---
;
; Naprogramujte funkci, která vypočítá výraz f(x,y) uvedený níže. Funkci jsou předávány parametry x a y
; na zásobníku v pořadí od posledního k prvnímu (zprava doleva), parametry ze zásobníku uklízí volající 
; a výsledek funkce se vrací v FPU v registru ST0 (konvence jazyka C).
;
;
;           A      (y + x - 6.225)/43 - sin(4 - 2*pi*y)
; f(x,y) = --- = -------------------------------------------
;           B              y - sqrt(abs(x))
;
;
; float task32(float x, float y)
;
; Vstup:
;   x: 32bitové číslo v plovoucí řádové čárce ve formátu IEEE754
;   y: 32bitové číslo v plovoucí řádové čárce ve formátu IEEE754
;
; Výstup:
;   ST0 = +Inf <=> A >= 0 && B == 0 (tedy čitatel >= 0 a jmenovatel == 0)
;   ST0 = -Inf <=> A < 0 && B == 0 (tedy čitatel <  0 a jmenovatel == 0)
;   ST0 = f(x,y) v ostatních případech
;
; Důležité:
;   Ve funkci NEsmíte použít instrukci FINIT (při odevzdání bude tato instrukce
;     z kódu odstraněna), předpokládejte, že registry koprocesoru jsou prázdné.
;   Ve funkci NEsmíte použít pro svá data datový segment (zásobník použít lze).
;   Funkce musí zachovat obsah všech registrů kromě registru EAX a příznakového registru.
;   Funkce musí vyprázdnit všechny registry FPU kromě ST0, kde bude výsledek funkce.
;   Konstantu lze vygenerovat direktivou __float32__(x) například takto: MOV EAX,__float32__(-4.45).
;   Konstantu lze do ST0 nahrát přes zásobník pomocí direktivy __float32__(x) takto: 
;       PUSH __float32__(10.5)
;       FLD dword [ESP]
;       ADD ESP,4
;
; Hodnocení: až 5 bodů.
;
task32:
    fld dword [esp+8]           ;           y
    fld dword [esp+4]           ;   x       y
    fabs
    fsqrt
    fsubp
    
    fld dword [esp+8]   
    fldpi
    fmul
    
    fld1
    fadd st0, st0
    
    fmul
    
    push __float32__(4.0)
    fld dword [esp]
    add esp, 4    
    
    fxch
    
    fsubp
    fsin
    
    fld dword [esp+8]
    fld dword [esp+4]
    faddp
    
    push __float32__(6.225)
    fld dword [esp]
    add esp, 4
    
    fsubp
    
    push __float32__(43.0)
    fld dword [esp]
    add esp, 4
    
    fdivp
    
    fxch
    fsubp
    
    ;st0 = A
    ;st1 = B
    
    ;+Inf <=> A >= 0 && B == 0
    fldz
    fcomi st1
    jae .neginf
    fcomi st2
    jne .neginf
    
    faddp
    fstp st0
    fstp st0
    
    push eax
    mov eax, 0x7F800000
    push eax
    fld dword [esp]
    add esp, 4
    pop eax
    
    jmp .end
    
    ;-Inf <=> A < 0 && B == 0
    .neginf:
    fcomi st1
    jb .fx
    fcomi st2
    jne .fx
    
    faddp
    fstp st0
    fstp st0
    
    push eax
    mov eax, 0xFF800000
    push eax
    fld dword [esp]
    add esp, 4
    pop eax   
    
    jmp .end 
    
    .fx:
    fstp st0
    fxch
    fdivp
    
    .end:
    ret
