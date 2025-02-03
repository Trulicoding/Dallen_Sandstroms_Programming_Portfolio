/*
Dallen Sandstrom
Project 8
File: DSPR8.cpp
This project is meant to demonstrate binomial distribution of probablility.
*/
#include <iostream>
#include <cmath>
using namespace std;
long long int permutations(int n, int r){
long long int p = 1;
for (int i = n; i > (n - r); i--) {
p *= i;
}
return p;
}
long long int combinations(int n, int r){
long long int c = permutations(n,r);
for (int i = r; i > 1; i--){
c /= i;
}
return c;
}
double binomial(int n, int k, double p){ // Bernoulli trials
return (double) combinations(n,k) * pow(p,k) * pow(1.0 - p, n - k);
}
int main(){
cout << "60 cars at a dealer, 3 dead batteries. If we check 10, what is the
probability no more than 1 will have a dead battery?" << endl;
cout << "Probability is: " << (double) (combinations(3,0) * combinations(57,10)
+ combinations(3,1) * combinations(57,9)) / combinations(60,10) << endl;
cout << "Auto recall: 8% have defect. If we test 20, what is the probability
that at most 2 will have the defect?" << endl;
cout << "Probability is: " << (binomial(20, 0, .08) + binomial(20, 1, .08) +
binomial(20, 2, .08)) << endl << endl;
cout << "Thanks!!" << endl << "Test value for student binomial(20,2,0.08): "
<< binomial(20, 2, .08) << endl;
return 0;
}