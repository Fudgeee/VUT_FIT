% Zadání č. 40:
% Napište program řešící úkol daný predikátem u40(LIN), kde LIN je vstupní 
% celočíselný seznam s nejméně dvěma čísly. Predikát je pravdivý (má hodnotu 
% true), pokud se v seznamu LIN pravidelně střídají lichá a sudá čísla, 
% jinak je nepravdivý (má hodnotu false).

% Testovací predikáty:
u40_1:- u40([4,-3,2,1,8,3,8,-1]).			% true
u40_2:- u40([4,-3,2,1,8,4,8,-1]).			% false
u40_3:- u40([-3,2]).					% true
u40_r:- write('Zadej LIN: '),read(LIN),u40(LIN).

u40(LIN):-list(LIN),!.

list([P1]):-true.
list([P1,P2|ZV]):-list([P2|ZV]),even(P1,P11),even(P2,P22),P11=\=P22.

even(A,0):-A mod 2=:=0.
even(A,1):-A mod 2=\=0. 