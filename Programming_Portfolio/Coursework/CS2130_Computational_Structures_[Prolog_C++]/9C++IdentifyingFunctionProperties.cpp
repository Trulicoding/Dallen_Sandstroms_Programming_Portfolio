/*
Dallen Sandstrom
Program 4
File: DSPR4.cpp
This program is meant to determine whether f is a valid function, one-to-one, onto,
and/or a bijection.
*/
#include <iostream>
using namespace std;
int main(){
int x[5],y[5];//arrays to store functions.
int numpairs;
bool valid = true;
bool repeat = false;
bool oneToOne = false;
bool onto = true;
bool found = false;
//Read Set
do{
cout << "Please enter the number of ordered pairs:\n";
cin >> numpairs;
if (numpairs > 5 || numpairs < 0){
cout << "The amount you entered was invalid, please try again." << endl;
}
}while(numpairs > 5 || numpairs < 0);
for (int i=0; i < numpairs; i++){
cout << "Enter Pair " << (i+1) << ": \n";
cin >> x[i];
cin >> y[i];
valid = valid && ((x[i] > 0 && x[i] <= 5) && (y[i] > 0 && y[i] <= 5));
}
//check for repeated value
for(int i=0; i < numpairs && !repeat; i++){
for(int j=i+1; j < numpairs && !repeat; j++){
repeat = (x[i]==x[j]);
//cout << x[i] << ", " << x[j] << " R: " << repeat << endl;
}
}
valid = valid && !repeat;
//Check if one-to-one
for(int i=0; i < numpairs && !oneToOne; i++){
for(int j=i+1; j < numpairs && !oneToOne; j++){
oneToOne = (y[i]==y[j]);
}
}
//Check if onto
for(int i = 0; i < numpairs && onto; i++){
found = false;
for(int j = 0; j < numpairs; j++){
//cout << x[i] << ", " << y[j] << endl;
if (x[i] == y[j]){
found = true;
break;
}
}
onto = found;
}
//Outputs
if (valid){
cout << "Valid" << endl;
if (!oneToOne){
cout << "1-to-1" << endl;
}
else{
cout << "Not 1-to-1" << endl;
}
if (onto){
cout << "Onto" << endl;
}
else{
cout << "Not Onto" << endl;
}
if (!oneToOne && onto){
cout << "Bijection" << endl;
}
else{
cout << "Not Bijection" << endl;
}
}
else{
cout << "Not Valid" << endl;
}
return 0;
}