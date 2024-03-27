%include "rw32-2020.inc"

section .data    
        a dd 1.5,-100.5,30000.300,-434.434,0.0,1.0,-1.0,0.0001,1.5,200.75
        errorCode dd -1
       
section .text
CMAIN:
    push ebp
    mov ebp,esp
    
    mov ecx,10
    mov esi,a 
    call task31
    
    push errorCode
    push __float32__(20.0)
    push __float32__(10.0)
    call task32
    add esp,12

    mov esp,ebp
    pop ebp
    ret    
;
;--- Ukol 1 --- 
;
; Naprogramujte funkci task31, ktera pomoci funkce 'qsort' jazyka C vzestupne (od nejmensiho k nejvetsimu)
; seradi pole prvku typu 'float' (32bitova hodnota v plovouci radove carce).
;
; K reseni tohoto problemu musite vyuzit funkci jazyka C:
;
;   void qsort( void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *) )
;
; ktera seradi pole prvku na adrese "ptr", ktere ma "count" prvku, kazdy o velikosti "size" bytu.
; Pro porovnani dvojice prvku se vyuziva funkce "comp", kterou musite naprogramovat, a ktera
; je definovana takto:
;
;   int comp(const void *a, const void *b)
;
; Funkce "comp" porovna hodnotu na adrese "a" s hodnotou na adrese "b" a v zavislosti na ucelu 
; pouziti vrati jako vysledek cele cislo se znamenkem takto ("x" je libovolna hodnota, typicky 1):
;
;    -x <=> *a < *b           -x <=> *a > *b  
;     0 <=> *a == *b   nebo    0 <=> *a == *b
;     x <=> *a > *b            x <=> *a < *b
;
; Vstup:
;   ECX = pocet prvku pole (32bitova hodnota se znamenkem)
;   ESI = ukazatel na pole 32bitovych hodnot v plovouci radove carce (float)
;
; Vystup:
;   EAX = 3 v pripade, ze ESI == 0 a zaroven ECX < 0
;   EAX = 2 v pripade, ze ECX < 0
;   EAX = 1 v pripade, ze ESI == 0
;   EAX = 0 v ostatnich pripadech
;
; Dulezite:
;   * Funkce musi zachovat obsah vsech registru krome EAX a priznakoveho registru.
;   * Zasobnikovy ramec neni potreba.
;   * Funkce "qsort" muze menit obsah registru ECX a EDX => pokud je pouzivate, schovejte si je.
;
; Hodnoceni: az 5 bodu.
; 
task31:
    ; zde zadejte kod funkce task31
    ret
;
;--- Ukol 2 ---
;
; Naprogramujte funkci:
;
;         float task32(float x, float y, int *pError)
;
; ktera vypocita hodnotu funkce f(x,y) uvedene nize v bode (x, y), ulozi indikator chyby 
; vypoctu na adresu pError (v pripade, ze lze vyraz vypocitat, vrati se hodnota 1, jinak
; hodnota 0) a vrati funkcni hodnotu funce f v bode (x, y).
;
; Funkci jsou predavany parametry x, y a pError na zasobniku v poradi od posledniho
; k prvnimu (zprava doleva), parametry ze zasobniku uklizi volajici a vysledek funkce 
; se vraci v FPU v registru ST0 (konvence jazyka C).
;
;
;           A      abs(x - y + 7.725)/37 - sin(4 - 2*pi*x)
; f(x,y) = --- = ---------------------------------------------
;           B              x*sqrt(y)
;
;
; Vstup:
;   x: 32bitove cislo v plovouci radove carce ve formatu IEEE754 (float)
;   y: 32bitove cislo v plovouci radove carce ve formatu IEEE754 (float)
;   pError: ukazatel na 32bitove cele cislo se znamenkem
;
; Vystup:
;   * pokud (x, y) ? D(f) (~ hodnotu funkce lze vypocitat), pak: *pError = 0, ST0 = f(x,y)
;   * pokud (x, y) ? D(f) (~ hodnotu funkce nelze vypocitat), pak: *pError = 1, ST0 = NaN (Not a Number)
;
; Dulezite:
;   * Ve funkci NEsmite pouzit instrukce FINIT, FCLEX, FNCLEX, FFREE (pri odevzdani budou 
;     z kodu odstraneny), predpokladejte, ze FPU je jiz inicializovano.
;   * Ve funkci NEsmite pouzit pro sva data datovy segment (zasobnik pouzit lze).
;   * Funkce musi zachovat obsah vsech registru krome registru EAX a priznakoveho registru.
;   * Funkce musi vyprazdnit vsechny registry FPU krome ST0, kde bude vysledek funkce.
;
; Hodnoceni: az 5 bodu.
;
task32:
    enter 0,0
    finit
    
    leave
    ret
