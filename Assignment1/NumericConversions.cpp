/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n) {
	if (n<0) return "-" + intToString(-n);
	if (n<10) return string() + char(n + '0');
	return intToString(n/10) + char((n%10)+'0');
}

int stringToInt(string str) {
	if (str[0]=='-') return (-1)*stringToInt(str.substr(1));
	if (str.length()==1) return str[0]-'0';
	return str[str.length()-1]-'0' + 10*stringToInt(str.substr(0,str.length()-1));
}

/* Main program */

int main() {
    int n;
	cin>>n;
	cout<<intToString(n)<<endl;

	string s;
	cin>>s;
	cout<<stringToInt(s)<<endl;

    return 0;
}
