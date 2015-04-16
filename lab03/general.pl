%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Circuit Independent Part %%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Introducing Signal and Connectivity

:- dynamic signal/2.

signal(X):-
	signal(X,1), !.
signal(X):-
    signal(X,0), !,fail.

signal(X):-
	connected(Y,X), !,
	signal(Y).
signal(out(1,X)):-
	!,out(1,X).

signal(X):-
	write('Circuit is Breaked from gate '),tab(1),write_ln(X), !, fail.

% out -- Function

out(1,X):-
	type(X,and),
	signal(in(1,X)),
	signal(in(2,X)).
out(1,X):-
	type(X,or),
	(signal(in(1,X)) | signal(in(2,X))).
out(1,X):-
	type(X,not),
	signal(in(1,X)), !,fail.
out(1,X):-
	type(X,not).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%% )---)__            %%%%%%%%%%%%%%%%
%%%%%%%%% )__|-)--)--        %%%%%%%%%%%%%%%%

%%%%%%%%%%%%%  Defining XOR %%%%%%%%%%%%%%%%%
type(a1,not).
type(a2,not).
type(a3,and).
type(a4,and).
type(a5,or).

connected(a,in(1,a1)).
connected(a,in(1,a3)).
connected(b,in(1,a2)).
connected(b,in(1,a4)).
connected(out(1,a1),in(2,a4)).
connected(out(1,a2),in(2,a3)).
%connected(out(1,a3),in(1,a5)).
%connected(out(1,a4),in(2,a5)).
connected(out(1,a5),c).

%%%%%%%% Verifying XOR %%%%%%%%%%%%%%%%%%%%

verify(xor, [A,B],C):-
	%write("Verifying XOR Circuit !!!!!").
	retractall(signal(_,_)),
	assert(signal(a,A)),
	assert(signal(b,B)),
	((signal(c), !, C==1) | C==0),
	write_ln('Verified !!!!').
