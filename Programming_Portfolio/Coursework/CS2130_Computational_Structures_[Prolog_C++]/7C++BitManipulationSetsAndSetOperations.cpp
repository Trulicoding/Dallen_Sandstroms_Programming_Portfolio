/*
Dallen Sandstrom
Program 3
File: DSPR3.cpp
This program is meant to demonstrate the ability to represent data, such as sets,
using bit-strings
and to perform the appropriate logical operations on those representations to
compute the desired results.
*/
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
void printSet(int theSet){
bool needComma = false;
cout << "{";
for(int i = 0; i < 10; i++){
if (theSet & (1 << i)){
if (needComma){//Very elegant
cout << ", ";
}
cout << i;//The value associated with the true bit in the bitstring
needComma = true;
}
}
cout << "}";
}
int readSet(){//Takes user input and outputs in bitSet form
int baseInput;
int inputSize;
int theSet = 0;
do{ // theSet size prompt
cin >> inputSize;
if(inputSize < 0 || inputSize > 10){
cout << "Value entered is not allowed, please try again.\n";
};
}while(inputSize < 0 || inputSize > 10);
for (int i = 1; i < inputSize+1; i++){//theSet element collection
do{//The enter element prompt
cout << "please enter element " << i << ": ";
cin >> baseInput;
if(baseInput < 0 || baseInput > 9){
cout << "Value entered is not allowed, please try again.\n";
};
/*
if(theSet & (1 << baseInput)){
cout << "That value has already been entered, please try again.\n";
}
*/
}while(baseInput < 0 || baseInput > 9/* || (theSet & (1 << baseInput))*/);
theSet = theSet | (1 << baseInput);
}
return theSet;
}
int main(){
cout << "CS 2130 - Computational Structures Dallen Sandstrom\n"
"This program reads in the values of two sets and displays\n"
"the results of several operations on the sets.\n\n";
int setA;
int setB;
//Inputs and calls to readSet
cout << "Please enter set A size: ";
setA = readSet();
cout << "Please enter set B size: ";
setB = readSet();
cout << "\nThe sets you entered are:";
cout << "\nSet A = ";
printSet(setA);
cout << "\nSet B = ";
printSet(setB);
//Set operations
cout << "\n\nComplement of A\n";
printSet(~setA);
cout << "\nUnion of A and B\n";
printSet(setA | setB);
cout << "\nIntersection of A and B\n";
printSet(setA & setB);
cout << "\nDifference of A and B\n";
printSet(setA & ~setB);
cout << "\nSymmetric difference of A and B\n";
printSet(setA ^ setB);
}