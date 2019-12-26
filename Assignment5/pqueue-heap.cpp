/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

#define BEGIN_ARRAY_SIZE 10

HeapPriorityQueue::HeapPriorityQueue() {
	length = 0;
	arrLength = BEGIN_ARRAY_SIZE;
	mas = new string[BEGIN_ARRAY_SIZE];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] mas;
}

int HeapPriorityQueue::size() {
	return length;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

void HeapPriorityQueue::grow() {
	arrLength *= 2;
	string* newMasive = new string[arrLength];
	for (int i = 0; i < length; i++)
		newMasive[i] = mas[i];

	delete[] mas;
	mas = newMasive;
}

bool isMorePriority4(string str1,string str2) {
	return str1 < str2;
}

void HeapPriorityQueue::bubbleUp() {
	int curr = length - 1;
	while (curr > 0) {
		if (!isMorePriority4(mas[curr], mas[curr / 2])) return;

		swap(mas[curr], mas[curr / 2]);
		curr /= 2;
	}
}

void HeapPriorityQueue::bubbleDown() {
	int curr = 0;
	while (curr < length) {
		if (2 * curr >= length) return;

		int minIndex = 2 * curr;
		if (minIndex + 1 < length && isMorePriority4(mas[minIndex + 1], mas[minIndex])) minIndex++;

		if (!isMorePriority4(mas[minIndex], mas[curr])) return;

		swap(mas[curr], mas[minIndex]);
		curr = minIndex;
	}
}

void HeapPriorityQueue::enqueue(string value) {
	if (size() + 1 >= arrLength) grow();
	mas[length++] = value;
	bubbleUp();
}

string HeapPriorityQueue::peek() {
	if (size() == 0) error("Queue is empty");
	return mas[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (size() == 0) error("Queue is empty");

	string ans = mas[0];
	swap(mas[0], mas[length - 1]);
	length--;
	bubbleDown();

	return ans;
}
