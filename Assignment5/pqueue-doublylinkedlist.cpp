/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	length = 0;
	first = new NodeT;
	last = new NodeT;

	first->next = last;
	last->prev = first;

	first->prev = NULL;
	last->next = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	NodeT* next = first;
	while (next != NULL) {
		NodeT* tmp = next->next;
		delete next;
		next = tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	length++;
	NodeT* newElement = new NodeT;
	newElement->value = value;

	newElement->next = first->next;
	first->next->prev = newElement;

	first->next = newElement;
	newElement->prev = first;
}

bool isMorePriority3(string str1,string str2) {
	return str1 < str2;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (size() == 0) error("Queue is Empty");

	string ans = first->next->value;
	NodeT* next = first->next->next;

	while (next != last) {
		if (isMorePriority3(next->value, ans)) ans = next->value;
		next = next->next;
	}

	return ans;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (size() == 0) error("Queue is Empty");

	NodeT* ans = first->next;
	NodeT* next = first->next->next;
	length--;

	while (next != last) {
		if (isMorePriority3(next->value, ans->value)) ans = next;
		next = next->next;
	}

	string res = ans->value;
	ans->prev->next = ans->next;
	ans->next->prev = ans->prev;

	delete ans;
	return res;
}
