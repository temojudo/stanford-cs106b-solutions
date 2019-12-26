/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "queue.h"
#include "set.h"
#include "console.h"
#include "lexicon.h"
using namespace std;

Set<string> used;
Queue <Queue<string> > myQueue;


void getNewWords(Queue<string> &now,Lexicon &words) {
	for (int i=0;i<now.back().length();i++) {
		for (char ch='a';ch<='z';ch++) {
			string word=now.back();
			word[i]=ch;
			if (words.contains(word) && !used.contains(word)) {
				used.add(word);
				Queue<string> copy = now;
				copy.enqueue(word);
				myQueue.enqueue(copy);
			}
		}
	}

}

Queue<string> path(string filename,string word1,string word2) {
	Lexicon words(filename);
	
	used.add(word1);
	Queue <string> w;
	w.enqueue(word1);
	myQueue.enqueue(w);
	
	if (words.contains(word1) && words.contains(word2))
		while (!myQueue.isEmpty()) {
			Queue<string> now = myQueue.dequeue();
			if (now.back()==word2) return now;
			getNewWords(now,words);
		}

	Queue<string> q; // return empty queue
	return q;
}

int main() {
	string word1,word2;
	cin>>word1>>word2;

	if (word1==word2) {
		cout<<"bingo"<<endl;
		return 0;
	}

	if (word1.length()!=word2.length()) {
		cout<<"no such path"<<endl;
		return 0;
	}

	Queue<string> final = path("EnglishWords.dat",word1,word2);
	if (final.isEmpty()) {
		cout<<"no such path"<<endl;
		return 0;
	}

	while(!final.isEmpty())
		cout<<final.dequeue()<<" ";

	cout<<endl;
	return 0;
}
