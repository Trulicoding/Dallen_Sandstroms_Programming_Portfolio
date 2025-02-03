% Dallen Sandstrom
% Homework 1
% File: DSHW1.pl
% This is a practice Prolog program that creates a family tree
%
%

% biologically female family members
female(ann).
female(beth).
female(liz).
female(sue).
female(jill).
female(mary).
female(carol).

% biologically male family members
male(bob).
male(ted).
male(bill).
male(sam).
male(harry).
male(john).
male(matt).

% parental relationships
parentof(beth,bill).
parentof(bill,jill).
parentof(bill,liz).
parentof(ann,jill).
parentof(ann,liz).
parentof(ann,ted).
parentof(liz,matt).
parentof(matt,john).
parentof(bob,carol).
parentof(harry,sue).
parentof(harry,sam).
parentof(carol,sue).
parentof(carol,sam).
parentof(sue,mary).
parentof(mary,john).

% Our rules come next
childof(Child,Parent) :- parentof(Parent,Child).
siblings(Sib1,Sib2) :- parentof(Parent,Sib1),
    parentof(Parent,Sib2),
	Sib1 \== Sib2.
sisterof(Sis, Sib) :- siblings(Sis, Sib),
    female(Sis).
%Ancestor Recursion
%added the following for homework 2
ancestor_of(A,B) :- parentof(A,B).
ancestor_of(A,B) :- parentof(A,C),ancestor_of(C,B).
%for counting the genrations
ancestor_gen(A,B,G) :- parentof(A,B),G is 1.
ancestor_gen(A,B,G) :- parentof(A,C),ancestor_gen(C,B,F),G is F+1.

% Gates
myxor(0,0,0).
myxor(0,1,1).
myxor(1,0,1).
myxor(1,1,0).

mynand(0,0,1).
mynand(0,1,1).
mynand(1,0,1).
mynand(1,1,0).

mycircuit(X,Y,Z,F) :- myxor(X,Y,T1), myxor(T1,Z,T2), mynand(T1,T2,F),
    write(X),write(' '),write(Y),write(' '),write(Z),write(' '),write(F),write('\n').