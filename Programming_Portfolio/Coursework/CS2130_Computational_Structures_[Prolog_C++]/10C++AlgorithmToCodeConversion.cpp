/*
Dallen Sandstrom
Homework 7
File: DSHW7.cpp
This program will use a given algorithm
to find the prime factorization of an input.
*/
#include <iostream>
using namespace std;
int main(){
char usrResp;
int usrInput;
int k;
while (tolower(usrResp) != 'n'){ //main loop
cout << "Please enter a positive integer for prime factorization: ";
cin >> usrInput;
//Cheking for valid response
if (usrInput < 2){
cout << "Invalid Response";
break;
}
cout << "The prime factorization of " << usrInput << " is:" << endl;
//The prime factorization algorithm
k = usrInput;
for (int i = 2; i*i <= usrInput; i++){
while(k % i == 0){
cout << i << " ";
k = k/i;
}
}
if (k > 1){
cout << k;
}
//Algorithm end
cout << "\n\nWould you like to try another number? (N for no, anything else
is yes: n): ";
cin >> usrResp;
}
cout << "Bye!!";
}