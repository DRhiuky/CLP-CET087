% Exercicio 1-------------------------------------------------------------------
:- use_module(library(clpfd)).

expr --> termo, [+], expr.
expr --> termo, [-], expr.
expr --> termo.
termo --> fator, [*], termo.
termo --> fator, [/], termo.
termo --> fator.
fator --> [X], {integer(X)}.
fator --> ['('], expr, [')'].

%-----------------------------

% 1 + 2 * 3
?- phrase(expr, [1,+,2,*,3]).
true.

% 4 - 5 / 1
?- phrase(expr, [4,-,5,/,1]).
true.

% (6 + 7) * 8
?- phrase(expr, ['(',6,+,7,')',*,8]).
true.

% 9 * (10 - 11)
?- phrase(expr, [9,*,'(',10,-,11,')']).
true.

% 12 / (13 + 14)
?- phrase(expr, [12,/,'(',13,+,14,')']).
true.

% (15 - 16) / 17
?- phrase(expr, ['(',15,-,16,')',/,17]).
true.

% 18 * 19 + 20
?- phrase(expr, [18,*,19,+,20]).
true.

% 21 - 22 * 23
?- phrase(expr, [21,-,22,*,23]).
true.

% 24 / 25 + 26
?- phrase(expr, [24,/,25,+,26]).
true.

% (27 + 28) - 29
?- phrase(expr, ['(',27,+,28,')',-,29]).
true.


% Exercicio 2-------------------------------------------------------------------

expr(V) --> termo(T), rexpr(T, V).
rexpr(Acc, V) --> [+], termo(T), {Acc1 #= Acc + T}, rexpr(Acc1, V).
rexpr(Acc, V) --> [-], termo(T), {Acc1 #= Acc - T}, rexpr(Acc1, V).
rexpr(Acc, Acc) --> [].

termo(V) --> fator(F), rtermo(F, V).
rtermo(Acc, V) --> [*], fator(F), {Acc1 #= Acc * F}, rtermo(Acc1, V).
rtermo(Acc, V) --> [/], fator(F), {Acc1 #= Acc / F}, rtermo(Acc1, V).
rtermo(Acc, Acc) --> [].

fator(V) --> [V], {integer(V)}.
fator(V) --> ['('], expr(V), [')'].

%-----------------------------

?- phrase(expr(V), [1,+,2,*,3]).
V = 7.

?- phrase(expr(V), [4,-,5,/,1]).
V = -1.

?- phrase(expr(V), ['(',6,+,7,')',*,8]).
V = 104.

?- phrase(expr(V), [9,*,'(',10,-,11,')']).
V = -9.

?- phrase(expr(V), [12,/,'(',13,+,14,')']).
V = 0.4444444444444444.

?- phrase(expr(V), ['(',15,-,16,')',/,17]).
V = -0.058823529411764705.

?- phrase(expr(V), [18,*,19,+,20]).
V = 362.

?- phrase(expr(V), [21,-,22,*,23]).
V = -485.

?- phrase(expr(V), [24,/,25,+,26]).
V = 26.96.

?- phrase(expr(V), ['(',27,+,28,')',-,29]).
V = 26.


% Exercicio 3-------------------------------------------------------------------

expr --> term, rexpr.
rexpr --> [+], expr, {write('y=POP();x=POP();PUSH(xADDy)'), nl}.
rexpr --> [-], expr, {write('y=POP();x=POP();PUSH(xSUBy)'), nl}.
rexpr --> [].
term --> factor, rterm.
rterm --> [*], term, {write('y=POP();x=POP();PUSH(xMULy)'), nl}.
rterm --> [/], term, {write('y=POP();x=POP();PUSH(xDIVy)'), nl}.
rterm --> [].
factor --> [X], {integer(X)}, {write('PUSH('), write(X), write(')'), nl}.
factor --> ['('], expr, [')'].

%-----------------------------

?- phrase(expr, [1,+,2,*,3]).
PUSH(1)
PUSH(2)
PUSH(3)
y=POP();x=POP();PUSH(xMULy)
y=POP();x=POP();PUSH(xADDy)
true.

?- phrase(expr, [4,-,5,/,1]).
PUSH(4)
PUSH(5)
PUSH(1)
y=POP();x=POP();PUSH(xDIVy)
y=POP();x=POP();PUSH(xSUBy)
true.

?- phrase(expr, ['(',6,+,7,')',*,8]).
PUSH(6)
PUSH(7)
y=POP();x=POP();PUSH(xADDy)
PUSH(8)
y=POP();x=POP();PUSH(xMULy)
true.

?- phrase(expr, [9,*, '(' , 10,-,11 , ')']).
PUSH(9)
PUSH(10)
PUSH(11)
y=POP();x=POP();PUSH(xSUBy)
y=POP();x=POP();PUSH(xMULy)
true.

?- phrase(expr, [12,/, '(',13,+,14,')']).
PUSH(12)
PUSH(13)
PUSH(14)
y=POP();x=POP();PUSH(xADDy)
y=POP();x=POP();PUSH(xDIVy)
true.

?- phrase(expr, ['(',15,-,16,')',/,17]).
PUSH(15)
PUSH(16)
y=POP();x=POP();PUSH(xSUBy)
PUSH(17)
y=POP();x=POP();PUSH(xDIVy)
true.

?- phrase(expr, [18,*,19,+,20]).
PUSH(18)
PUSH(19)
y=POP();x=POP();PUSH(xMULy)
PUSH(20)
y=POP();x=POP();PUSH(xADDy)
true.

?- phrase(expr, [21,-,22,*,23]).
PUSH(21)
PUSH(22)
PUSH(23)
y=POP();x=POP();PUSH(xMULy)
y=POP();x=POP();PUSH(xSUBy)
true.

?- phrase(expr, [24,/,25,+,26]).
PUSH(24)
PUSH(25)
y=POP();x=POP();PUSH(xDIVy)
PUSH(26)
y=POP();x=POP();PUSH(xADDy)
true.

?- phrase(expr, ['(',27,+,28,')',-,29]).
PUSH(27)
PUSH(28)
y=POP();x=POP();PUSH(xADDy)
PUSH(29)
y=POP();x=POP();PUSH(xSUBy)
true.

% Exercicio 4-------------------------------------------------------------------

expr(V) --> term(V1), rexpr(V1, V).
rexpr(X, V) --> [+], expr(Y), {V is X + Y, write('y=POP(); x=POP(); PUSH(x ADD y)'), nl}.
rexpr(X, V) --> [-], expr(Y), {V is X - Y, write('y=POP(); x=POP(); PUSH(x SUB y)'), nl}.
rexpr(X, X) --> [].

term(V) --> factor(V1), rterm(V1, V).
rterm(X, V) --> [*], term(Y), {V is X * Y, write('y=POP(); x=POP(); PUSH(x MUL y)'), nl}.
rterm(X, V) --> [/], term(Y), {V is X / Y, write('y=POP(); x=POP(); PUSH(x DIV y)'), nl}.
rterm(X, X) --> [].

factor(V) --> [X], {integer(X), V = X, write('PUSH('), write(X), write(')'), nl}.
factor(V) --> ['('], expr(V), [')'].

%-----------------------------

% 1 + 2 * 3
?- phrase(expr(V), [1,+,2,*,3]).
PUSH(1)
PUSH(2)
PUSH(3)
y=POP(); x=POP(); PUSH(x MUL y)
y=POP(); x=POP(); PUSH(x ADD y)
V = 7.

% 4 - 5 / 1
?- phrase(expr(V), [4,-,5,/,1]).
PUSH(4)
PUSH(5)
PUSH(1)
y=POP(); x=POP(); PUSH(x DIV y)
y=POP(); x=POP(); PUSH(x SUB y)
V = -1.

% (6 + 7) * 8
?- phrase(expr(V), ['(',6,+,7,')',*,8]).
PUSH(6)
PUSH(7)
y=POP(); x=POP(); PUSH(x ADD y)
PUSH(8)
y=POP(); x=POP(); PUSH(x MUL y)
V = 104.

% 9 * (10 - 11)
?- phrase(expr(V), [9,*,'(',10,-,11,')']).
PUSH(9)
PUSH(10)
PUSH(11)
y=POP(); x=POP(); PUSH(x SUB y)
y=POP(); x=POP(); PUSH(x MUL y)
V = -9.

% 12 / (13 + 14)
?- phrase(expr(V), [12,/,'(',13,+,14,')']).
PUSH(12)
PUSH(13)
PUSH(14)
y=POP(); x=POP(); PUSH(x ADD y)
y=POP(); x=POP(); PUSH(x DIV y)
V = 0.7058823529411765.

% (15 - 16) / 17
?- phrase(expr(V), ['(',15,-,16,')',/,17]).
PUSH(15)
PUSH(16)
y=POP(); x=POP(); PUSH(x SUB y)
PUSH(17)
y=POP(); x=POP(); PUSH(x DIV y)
V = -0.058823529411764705.

% 18 * 19 + 20
?- phrase(expr(V), [18,*,19,+,20]).
PUSH(18)
PUSH(19)
y=POP(); x=POP(); PUSH(x MUL y)
PUSH(20)
y=POP(); x=POP(); PUSH(x ADD y)
V = 362.

% 21 - 22 * 23
?- phrase(expr(V), [21,-,22,*,23]).
PUSH(21)
PUSH(22)
PUSH(23)
y=POP(); x=POP(); PUSH(x MUL y)
y=POP(); x=POP(); PUSH(x SUB y)
V = -485.

% 24 / 25 + 26
?- phrase(expr(V), [24,/,25,+,26]).
PUSH(24)
PUSH(25)
y=POP(); x=POP(); PUSH(x DIV y)
PUSH(26)
y=POP(); x=POP(); PUSH(x ADD y)
V = 26.96.

% (27 + 28) - 29
?- phrase(expr(V), ['(',27,+,28,')',-,29]).
PUSH(27)
PUSH(28)
y=POP(); x=POP(); PUSH(x ADD y)
PUSH(29)
y=POP(); x=POP(); PUSH(x SUB y)
V = 26.
