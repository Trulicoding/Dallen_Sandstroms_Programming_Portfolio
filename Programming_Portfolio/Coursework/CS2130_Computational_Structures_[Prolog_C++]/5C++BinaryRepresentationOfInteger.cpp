/*
Dallen Sandstrom
Homework 3
File: DSHW.cpp
This program represents an integer in binary data.
*/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
void printBinary(int theValue){
for (int i = 31; i >= 0; i--) { // note we are looping from high bits to low
if ((theValue >> i & 1) > 0) { // if the bit at position i is one
cout << "1 "; // print a one followed by a space
} else { // otherwise the bit is zero
cout << "0 "; // print a zero followed by a space
}
} // end of the for loop, but we still need to print a newline
cout << endl;
}
int main(){
int theInput;
cout << "Enter your integer to display in binary bit representation: " << endl;
//the first integer request you see
do{ //Runs the request until you input 0
cin >> theInput;
printBinary(theInput);
cout << endl << "Enter 0 to quit, input another integer to again display it in
binary bit representation: " << endl;
} while(theInput != 0); //end of do while loop
cout << endl << "0 entered, ending program"; //program end
}