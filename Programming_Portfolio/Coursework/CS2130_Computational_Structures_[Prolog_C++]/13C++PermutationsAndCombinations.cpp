/*
Dallen Sandstrom
Project 7
File: DSPR7.cpp
This project is meant to investigate the usage of permutations and combinations
and to recognize the limitations imposed by finite storage and representation of
integer values.
*/
#include <iostream>
using namespace std;
unsigned long long int permutations(int n, int r){
unsigned long long int p = 1;
for (int i = n; i > (n - r); i--) {
p *= i;
}
return p;
}
unsigned long long int combinations(int n, int r){
unsigned long long int c = permutations(n,r);
for (int i = r; i > 1; i--){
c /= i;
}
return c;
}
int main(){
cout << "Check for correctness of functions:" << endl;
cout << "permutations: P(35, 12) = " << permutations(35, 12) << "
(should be 399703747322880000)" << endl;
cout << "combinations: C(23, 11) = " << combinations(23, 11) << "
(should be 1352078)" << endl << endl;
cout << "Ways of selecting doctors for the first batch: " << combinations(12,
4) << endl;
cout << "Ways of selecting nurses for the first batch: " << combinations(36,
12) << endl;
cout << "Ways to administer the first dose: " << combinations(12, 4) *
combinations(36, 12) << endl << endl;
cout << "Ways of selecting doctors for the second batch: " << combinations(8,
4) << endl;
cout << "Ways of selecting nurses for the second batch: " << combinations(24,
12) << endl;
cout << "Ways to administer the second dose: " << combinations(8, 4) *
combinations(24, 12) << endl << endl;
cout << "Total number of was to administer all doses:" << endl <<
combinations(12, 4) * combinations(36, 12) << " * " << combinations(8, 4) *
combinations(24, 12) << " * 1" << endl;
cout << "The numeric answer is: 117,280,955,571,359,580,000" << endl << endl;
cout << "The number of ways to distribute 4 bonuses to 23 people if different
is: " << permutations(23, 4) << endl;
cout << "If the bonuses are the same, there are: " << combinations(23, 4) <<
endl;
return 0;
}