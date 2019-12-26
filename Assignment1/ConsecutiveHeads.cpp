/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
    int head=0,tail=0,count=0;

	while(true) {
		if(randomChance(0.5)) {
			cout<<"heads"<<endl;
			head++;
			tail=0;
		} else {
			cout<<"tails"<<endl;
			tail++;
			head=0;
		}
		
		count++;

		if (head==3) {
			cout<<"It took "<<count<<" flips to get 3 consecutive heads."<<endl;
			return 0;
		}

		if (tail==3) {
			cout<<"It took "<<count<<" flips to get 3 consecutive tails."<<endl;
			return 0;
		}
	}

    return 0;
}
