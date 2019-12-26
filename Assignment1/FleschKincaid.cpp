/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

bool isVowel(char ch) {
	if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='y')
		return true;

	if (ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' || ch=='Y')
		return true;

	return false;
}

bool containsVowel(string word) {
	for (int i=0;i<word.length();i++)
		if (isVowel(word[i]))
			return true;

	return false;
}

bool containsSentenceSign(string str) {
	if (containsVowel(str))
		return false;

	for (int i=0;i<str.length();i++)
		if (str[i]=='!' || str[i]=='.' || str[i]=='?')
			return true;

	return false;
}

int getWords(string line) {
	int count = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if ((word[0]>='a' && word[0]<='z') || (word[0]>='A' && word[0]<='Z') && !containsSentenceSign(word))
			count++;
	}
	return count;
}

int getSentences(string line) {
	int count = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		if (containsSentenceSign(word))
			count++;
	}

	return count;
}

int numSyllables(string word) {
	int count=0;
	for (int i=0;i<word.length();i++) {
		if (isVowel(word[i])) {
			if (i!=(word.length()-1)) {
				if (!isVowel(word[i+1]))
					count++;
			} else {
				if (word[i]!='e')
					count++;
			}
		}
	}

	if (count==0 && containsVowel(word))
		return 1;

	return count;
}

int getSyllables(string line) {
	int count = 0;
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	while (scanner.hasMoreTokens()) {
		string word = scanner.nextToken();
		count+=numSyllables(word);
	}

	return count;

}

const double C0=-15.59;
const double C1=0.39;
const double C2=11.8;

int main() {
	double word=0,sent=0,syll=0;

	string file;
	ifstream fin;
	while (cout<<"Enter valid file name: ",cin>>file) {
		if (openFile(fin,file))
			break;
	}

	string line;
	while (getline(fin,line)) {
		word+=getWords(line);
		sent+=getSentences(line);
		syll+=getSyllables(line);
	}

	fin.close();
	if (sent<1) sent=1;
	if (word<1) word=1;

	double grade = C0+C1*(word/sent)+C2*(syll/word);
	cout<<"grade is: "<<grade<<endl;
    return 0;
}
