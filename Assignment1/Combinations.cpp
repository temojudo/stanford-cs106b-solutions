/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int comb(int a,int b) {
	if (a==0 && b==0) return 1;
	if (b==0) return comb(a-1,b);
	if (b==a) return comb(a-1,b-1);
	
	return comb(a-1,b-1) + comb(a-1,b);
}

int main() {
    int n,k;
	cin>>n>>k;
	cout<<comb(n,k)<<endl;
    return 0;
}
