/*
Dallen Sandstrom
Homework 10
File: DSHW10.cpp
This program will read repeated lines of input until a zero length
string is entered. It counts the number of occurrences for alphabetic
characters in the string and outputs the counts.
*/
#include <iostream>
using namespace std;
void outputCount(int counts[]) {
// function to output character counts
char i; // loop control variable
cout << "------------- The number of occurrences for each letter:
--------------\n";
for (i='A'; i <= 'Z'; i++) {
cout << i << " - " << counts[i-'A'] << " ";
if ( (i - 64) % 8 == 0) cout << endl;
}
cout << endl;
}
void countChars(int counts[], string inStr) {
// function to count the number of occurences of alphabetic characters in a string
for(const char &c : inStr) { // for all characters in the string
if (isalpha(c)) counts[toupper(c)-'A']++; // increment the count
}
}
int main(int argc, char *argv[]) {
string theInput = "";
int charCount[26] = {0};
do {
cout << "\nPlease enter a string, press return to stop: ";
getline(cin, theInput); // input an entire line of text
countChars(charCount, theInput); // use the function to count
characters
} while (theInput.length() > 0); // if the entered string had no characters
exit
cout << endl;
outputCount(charCount); // output the character count
cout << endl << endl;
return 0;
}