/*
Dallen Sandstrom
Homework 5
File: DSHW5.cpp
This assignment is meant to demonstrate recursive functions.
*/
#include <iostream>
#include <limits>
using namespace std;
void printRevString(string theString, int position){ //String reversal function
if (theString[position] != '\0'){
if (position != theString.length()-1){
printRevString(theString, position + 1);
cout << theString[position];
}
}
}
int sumRange(int val1, int val2){ //Summation function
int tempInt;
if (val1 == val2){
return val1;
}
if (val1 < val2){
tempInt = val1;
val1 = val2;
val2 = tempInt;
}
return (val1 + sumRange(val1-1, val2));
}
int main(){
int inputA;
int inputB;
string inputC;
//Part 1
cout << "Please enter your range of integers (on one or more lines)\n";
cin >> inputA;
cin >> inputB;
cout << "the sum of all the integers from " << inputA << " to " << inputB << " is
";
cout << sumRange(inputA ,inputB);
cout << endl;
//Part 2
cout << "Please enter a String: ";
cin.ignore(numeric_limits<streamsize>::max(), '\n');//clearing newline inputs from
buffe
getline(cin, inputC);
cout << "The reverse of your input is:\n";
printRevString(inputC, 0);
cout << endl;
}