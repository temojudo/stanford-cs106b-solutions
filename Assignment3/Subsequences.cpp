/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence) {
	if (text.length()==0) {
		if (subsequence.length()==0) 
			return true;

		return false;
	}

	if (text[0]==subsequence[0]) 
		return isSubsequence(text.substr(1),subsequence.substr(1));

	return isSubsequence(text.substr(1),subsequence);
}

int main() {
    string s1,s2;
	cin>>s1>>s2;
	cout<<isSubsequence(s1,s2)<<endl;
    return 0;
}
