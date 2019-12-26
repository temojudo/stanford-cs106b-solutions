/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	words = new Vector<string>();
}

VectorPriorityQueue::~VectorPriorityQueue() {
	delete words;
}

int VectorPriorityQueue::size() {
	return words->size();
}

bool VectorPriorityQueue::isEmpty() {
	return size()==0;
}

void VectorPriorityQueue::enqueue(string value) {
	words->add(value);
}

bool isMorePriority1(string str1,string str2) {
	return str1 < str2;
}

int getMinWordIndex(Vector<string>* &words) {
	int minIndex=0;
	for (int i=1;i<words->size();i++)
		if (isMorePriority1(words->get(i),words->get(minIndex)))
			minIndex=i;

	return minIndex;
}

string VectorPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty");

	int index=getMinWordIndex(words);
	return words->get(index);
}

string VectorPriorityQueue::dequeueMin() {
	if (isEmpty()) error("Queue is empty");

	int index=getMinWordIndex(words);
	string myWord=words->get(index);

	words->set(index, words->get(words->size() - 1));
	words->set(words->size() - 1, myWord);
	words->remove(words->size() - 1);

	return myWord;
}
