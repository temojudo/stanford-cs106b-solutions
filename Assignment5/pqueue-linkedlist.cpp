/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	length = 0;	
	first = new NodeT;
	first->next = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	NodeT* next = first;
	while (next != NULL) {
		NodeT* tmp = next->next;
		delete next;
		next = tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

bool isMorePriority2(string str1,string str2) {
	return str1 < str2;
}

void LinkedListPriorityQueue::enqueue(string value) {
	NodeT* next = first->next;
	NodeT* prev = first;

	NodeT* newElement = new NodeT;
	newElement->value = value;

	length++;
	while (next != NULL) {
		if (isMorePriority2(value,next->value)) {
			newElement->next = next;
			prev->next = newElement;
			return;
		}
		
		prev = next;
		next = next->next;
	}

	newElement->next = NULL;
	prev->next = newElement;
}

string LinkedListPriorityQueue::peek() {
	if (size() == 0) error("Queue is empty");
	return first->next->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (size() == 0) error("Queue is empty");

	NodeT* ans = first->next;	
	string res = ans->value;
	first->next = first->next->next;

	length--;
	delete ans;
	return res;
}
