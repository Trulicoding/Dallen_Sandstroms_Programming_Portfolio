% Dallen Sandstrom
% Program 2
% File: DSPR2.pl
% This program is used to demonstrate the ability to use Prolog to simulate circuitry

% Gates/Facts
myand(0,0,0).
myand(1,0,0).
myand(0,1,0).
myand(1,1,1).

myor(0,0,0).
myor(1,0,1).
myor(0,1,1).
myor(1,1,1).

myxor(0,0,0).
myxor(0,1,1).
myxor(1,0,1).
myxor(1,1,0).

mynot(1,0).
mynot(0,1).

% Circuit
circuit(A1,A0,B1,B0,S1,S0,Carryout) :- myor(A0,B0,R0), myand(A0,B0,R1), mynot(R1,R2), myand(R0,R2,S0),
   myor(A1,B1,R3), myand(A1,B1,R4), mynot(R4,R5), myand(R3,R5,R6), myor(R1,R6,R7), myand(R1,R6,R8), mynot(R8,R9), myand(R7,R9,S1),
   myor(R8,R4,Carryout).