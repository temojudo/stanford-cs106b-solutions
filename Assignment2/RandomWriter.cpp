/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "vector.h"
#include "console.h"
#include "filelib.h"
#include "map.h"
#include "queue.h"
#include "random.h"
using namespace std;

Map<string,Vector<char> > myMap;

string toString(Queue<char> myQueue) {
	string str="";
	while(!myQueue.isEmpty())
		str+=myQueue.dequeue();

	return str;
}

void fillMap(string &text,int k) {
	Queue<char> myQueue;
	for (int i=0;i<k;i++)
		myQueue.enqueue(text[i]);

	for (int i=k;i<text.length();i++) {
		myMap[toString(myQueue)]+=text[i];
		myQueue.dequeue();
		myQueue.enqueue(text[i]);
	}

}

string firstLetters() {
	int max=0;
	string word="";
	foreach (string str in myMap) 
		if (max<myMap[str].size()) {
			word=str;
			max=myMap[str].size();
		}

	return word;
}

int main() {
    string filename;
	ifstream fin;
	while (cout<<"Enter valid file name: ",cin>>filename) {
		if (openFile(fin,filename))
			break;
	}

	string text="",line;
	while (getline(fin,line))
		text+=line+"\n";

	int k;
	cout<<"Enter model k (but not too much): ";
	cin>>k;
	fillMap(text,k);
	
	string finalText = firstLetters();
	for (int i=k;i<2000;i++) {
		string next = finalText.substr(i-k,i);
		if (!myMap.containsKey(next)) break;
		finalText += myMap[next][randomInteger(0, myMap[next].size()-1)];
	}
	
	cout<<finalText<<endl;	
	return 0;
}
