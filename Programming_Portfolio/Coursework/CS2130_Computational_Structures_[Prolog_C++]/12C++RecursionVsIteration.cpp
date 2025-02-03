/*
Dallen Sandstrom
Homework 9
File: DSHW9.cpp
This assignment is meant to compare the efficiency of recursive and iterative
solutions to the same problem.
*/
#include <iostream>
using namespace std;
int fibo(int n) {
if(n < 2){
return n;
}
return fibo(n-1) - fibo(n-2);
}
int iterfib(int n) {
int fib = 0;
int n2 = 0;
int n1 = 1;
if (n < 2){
return n;
}
for (int i = 2; i <=n; i++){
fib = n1 + n2;
n2 = n1;
n1 = fib;
}
return n;
}
int main() {
int i;
// Get user input
cout << "Please enter a value to determine the Fibonacci sequence element for:
";
cin >> i;
cout << "The recursively determined result is: " << fibo(i) << std::endl;
cout << std::endl;
cout << "The iterative value is: " << iterfib(i) << std::endl;
cout << std::endl;
return 0;
}