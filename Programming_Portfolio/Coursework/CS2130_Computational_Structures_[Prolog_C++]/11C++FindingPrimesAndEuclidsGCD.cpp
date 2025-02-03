/*
Dallen Sandstrom
Project 6
File: DSPR6.cpp
This program will read in two numbers and determine the if either of the two are
prime
and then determine the greatest common divisor and the least common multiple of the
two integers.
*/
#include <iostream>
using namespace std;
int main(){
int a;
int b;
bool aPrime = true;
bool bPrime = true;
//Collect integers
cout << "This program reads in two integers and determines if they are \nprime.
It then computes the greatest common divisor of the \ntwo integers using Euclid's
Algorithm.\n\n";
cout << "Enter the first integer: ";
cin >> a;
cout << "Enter the second integer: ";
cin >> b;
cout << "\n\nResults:\n";
//Calculate input a's primeness
for (int i = 2; i*i <= a; i++){
if(a%i == 0){
aPrime = false;
break;
}
}
if (aPrime){
cout << a << " is a prime number.\n";
}else{
cout << a << " is not a prime number.\n";
}
for (int i = 2; i*i <= b; i++){
if(b%i == 0){
bPrime = false;
break;
}
}
//Calculate input b's primeness
if (bPrime){
cout << b << " is a prime number.\n";
}else{
cout << b << " is not a prime number.\n";
}
//Calculate and output the GCD
int x = a;
int y = b;
int r;
while (y != 0){
r = x % y;
x = y;
y = r;
}
cout << "The gcd(" << a << ", " << b << ") is " << x << ".\n";
//Find and output LCD
cout << "The lcd(" << a << ", " << b << ") is " << ((a*b)/x) << ".\n";
}