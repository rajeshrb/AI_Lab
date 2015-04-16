%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%% Full Adder %%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
:- [gates].
%%%%%%% Defining Ful_Adder Circuit %%%%%%%%%%%
type(a1,not).
type(a2,not).
type(a3,not).
type(b1,and).
type(b2,and).
type(b3,and).
type(b4,and).
type(b5,and).
type(b6,and).
type(b7,and).
type(b8,and).
type(b9,and).
type(b10,and).
type(b11,and).
type(c1,or).
type(c2,or).
type(c3,or).
type(c4,or).
type(c5,or).

connected(a,in(1,a1)).
connected(b,in(1,a2)).
connected(c,in(1,a3)).

connected(out(1,a1),in(1,b1)).
connected(out(1,a2),in(2,b1)).
connected(out(1,b1),in(1,b2)).
connected(c,in(2,b2)).

connected(out(1,a1),in(1,b3)).
connected(b,in(2,b3)).
connected(out(1,a3),in(2,b4)).
connected(out(1,b3),in(1,b4)).
connected(a,in(1,b5)).

connected(out(1,a2),in(2,b5)).
connected(out(1,a3),in(1,b6)).
connected(out(1,b5),in(2,b6)).

connected(a,in(1,b7)).
connected(b,in(2,b7)).
connected(c,in(2,b8)).
connected(out(1,b7),in(1,b8)).

connected(out(1,b2),in(1,c1)).
connected(out(1,b4),in(2,c1)).
connected(out(1,b6),in(1,c2)).
connected(out(1,b8),in(2,c2)).
connected(out(1,c1),in(1,c3)).
connected(out(1,c2),in(2,c3)).
connected(out(1,c3),d).
connected(a,in(1,b9)).
connected(b,in(2,b9)).
connected(b,in(1,b10)).
connected(c,in(2,b10)).
connected(c,in(1,b11)).
connected(a,in(2,b11)).
connected(out(1,b9),in(1,c4)).
connected(out(1,b10),in(2,c4)).
connected(out(1,c4),in(1,c5)).
connected(out(1,b11),in(2,c5)).
connected(out(1,c5),e).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%% Verifying Full_Adder Circuit %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

verify(full_adder, [X,Y,Z], [A,B]) :-
	retractall(signal(_,_)),
	assert(signal(a,X)),
	assert(signal(b,Y)),
	assert(signal(c,Z)),
    ((signal(d), !, A==1) | A==0),((signal(e), !, B==1) | B==0),
    write_ln(' Verified !!!!').
