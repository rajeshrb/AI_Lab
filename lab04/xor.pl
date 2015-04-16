%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%  XOR %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
:- [gates].
%%%%%%%%%% Defining XOR Circuit %%%%%%%%%%%

type(g1,not).
type(g2,not).
type(g3,and).
type(g4,and).
type(g5,or).

connected(a,in(1,g1)).
connected(a,in(1,g3)).
connected(b,in(1,g2)).
connected(b,in(1,g4)).
connected(out(1,g2),in(2,g3)).
connected(out(1,g1),in(2,g4)).
connected(out(1,g3),in(1,g5)).
connected(out(1,g4),in(2,g5)).
connected(out(1,g5),c).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Verifying XOR Circuit %%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

verify(xor, [I1,I2], O):-
retractall(signal(_,_)),
assert(signal(a,I1)),
assert(signal(b,I2)),
((signal(c), !, O==1) | O==0),
write_ln(' Verified !!!!'). 