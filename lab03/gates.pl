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

%%%%%%%%%%% For Connectivity %%%%%%%%%%
signal(X):-
        write('Circuit is Breaked from gate '),tab(1),write_ln(X), !, fail.

%%%%%%%%%% out -- Function %%%%%%%%%%%%

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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%