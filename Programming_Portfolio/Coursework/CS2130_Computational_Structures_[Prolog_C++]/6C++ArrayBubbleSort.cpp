/*
Dallen Sandstrom
Homework 4
File: DSHW4.cpp
This program bubble sorts an array and counts letters in an input.
*/
#include <iostream>
#include <cctype>
#include <array>
using std::cout;
using std::cin;
using std::endl;
using std::array;
using std::string;
int main() {
/*~~~~~~Part 1~~~~~~*/
int n = 20;
bool didSwap;
array<int, 20> toBeSorted = {4, 18, 27, 9, 3, 22, 16, 6, 12, 26, 8, 15, 25, 29,
2, 1, 20, 11, 19, 7}; //The random array I'll sort
for (int i = 0; i < n - 1; ++i) { //bubble sort
didSwap = false;
for (int j = n - 1; j > i; --j) {
if (toBeSorted[j] < toBeSorted[j - 1]) {
std::swap(toBeSorted[j], toBeSorted[j - 1]);
didSwap = true;
}
}
if (!didSwap) {
break;
}
}
//output
cout << "Sorted array: ";
for (int i = 0; i < n; ++i) {
cout << toBeSorted[i] << " ";
}
/*~~~~~~Part 2~~~~~~*/
cout << endl << endl << "Enter a string: ";
string input;
getline(cin, input);//Gets the input
string modifiedString;
array<int, 26> letterCount = {0}; //Array to store letter counts, initialized
to zero
for (char character : input) {
if (isalpha(character)) { //If character is a letter
modifiedString += toupper(character); //Add it to the modified string
letterCount[toupper(character) - 'A']++; //Increment count for the
letter
}
}
cout << "Modified string: " << modifiedString << endl;
cout << "Length of modified string: " << modifiedString.length() << endl <<
endl;
cout << "Letter Counts:" << endl;
for (int i = 0; i < 26; ++i) { //Lists each letter
char letter = 'A' + i;
cout << letter << " ";
}
cout << endl;
for (int i = 0; i < 26; ++i) { //Shows amount of all the letters
cout << letterCount[i] << " ";
}
return 0;
}