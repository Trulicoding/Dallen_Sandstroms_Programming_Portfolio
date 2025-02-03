% Dallen Sandstrom
% Program 1
% File: DSPR1.pl
% This program is used to determine if there are airline flights scheduled between a list of cities.

% Facts
from_to(dgz,qyy).
from_to(dgz,azi).
from_to(qyy,csi).
from_to(azi,tva).
from_to(csi,ppg).
from_to(tva,brw).
from_to(brw,csi).

% Rules
route(A,B,G) :- from_to(A,B),G is 0.
route(A,B,G) :- from_to(A,C),route(C,B,F),G is F+1.
