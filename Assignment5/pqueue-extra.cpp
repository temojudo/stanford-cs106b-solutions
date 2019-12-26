/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"

#define MAX_SIZE_STRINGS 100

bool isMorePriority5(string str1, string str2) {
	return str1 < str2;
}

ExtraPriorityQueue::ExtraPriorityQueue() {
	length = 0;
	priorityWordIndex = -1;
	buckets = new Vector<string>*[MAX_SIZE_STRINGS + 1];

	for (int i = 1; i <= MAX_SIZE_STRINGS; i++) {
		Vector<string>* vec = new Vector<string>();
		buckets[i] = vec;
	}

}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	for (int i = 1; i <= MAX_SIZE_STRINGS; i++)
		delete buckets[i];
}

int ExtraPriorityQueue::size() {
	return length;
}

bool ExtraPriorityQueue::isEmpty() {
	return size() == 0;
}

void ExtraPriorityQueue::enqueue(string value) {
	if (value.length() > MAX_SIZE_STRINGS) error("String size must be less than " + MAX_SIZE_STRINGS);

	length++;
	buckets[value.length()]->add(value);
	bubbleUp(buckets[value.length()]);

	if (priorityWordIndex == -1 || isMorePriority5(value, buckets[priorityWordIndex]->get(0)))
		priorityWordIndex = value.length();
}

string ExtraPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty");
	
	return buckets[priorityWordIndex]->get(0);
}

string ExtraPriorityQueue::dequeueMin() {
	if (isEmpty()) error("Queue is empty");

	length--;

	Vector<string>* vec = buckets[priorityWordIndex];
	string ans = vec->get(0);

	vec->set(0, vec->get(vec->size() - 1));
	vec->set(vec->size() - 1, ans);
	vec->remove(vec->size() - 1);

	bubbleDown(vec);
	changePriorityWordIndex();
	return ans;
}

void ExtraPriorityQueue::bubbleUp(Vector<string>* vec) {
	int curr = vec->size() - 1;
	while (curr > 0) {
		if (!isMorePriority5(vec->get(curr), vec->get(curr / 2))) return;

		/* swap function */
		string tmp = vec->get(curr);
		vec->set(curr, vec->get(curr / 2));
		vec->set(curr / 2, tmp);
		
		curr /= 2;
	}
}

void ExtraPriorityQueue::bubbleDown(Vector<string>* vec) {
	int curr = 0;
	while (curr < vec->size()) {
		if (2 * curr >= vec->size()) return;

		int minIndex = 2 * curr;
		if (minIndex + 1 < vec->size() && isMorePriority5(vec->get(minIndex + 1), vec->get(minIndex))) minIndex++;

		if (!isMorePriority5(vec->get(minIndex), vec->get(curr))) return;

		/* swap function */
		string tmp = vec->get(curr);
		vec->set(curr, vec->get(minIndex));
		vec->set(minIndex, tmp);

		curr = minIndex;
	}

}

void ExtraPriorityQueue::changePriorityWordIndex() {
	priorityWordIndex = -1;
	for (int i = 1; i <= MAX_SIZE_STRINGS; i++)
		if (buckets[i]->size() > 0 && (priorityWordIndex == -1 || 
			isMorePriority5(buckets[i]->get(0), buckets[priorityWordIndex]->get(0))))
			priorityWordIndex = i;
}
