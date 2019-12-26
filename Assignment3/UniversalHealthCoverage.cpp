/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
void fillResult(Vector<Set<string> >& myVec, Vector<Set<string> >& result) {
	Set<string> st; /* not to repeat locations */
	for (int i=0;i<myVec.size();i++)
		if (!myVec[i].isSubsetOf(st)) {
			st+=myVec[i];
			result+=myVec[i];
		}
}

bool canOffer(Vector<Set<string> >& myVec, Set<string>& cities, Vector<Set<string> >& result) {
	Set<string> all;
	for (int i=0;i<myVec.size();i++)
		all+=myVec[i];

	if (all==cities) {
		fillResult(myVec,result);
		return true;
	}

	return false;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector<Set<string> >& result,
							   Vector<Set<string> > myVec) {

	if (myVec.size()>numHospitals) return false;
	if (canOffer(myVec,cities,result)) return true;

	for (int i=0;i<locations.size();i++) {
		Vector<Set<string> > st = myVec;
		st.add(locations[i]);
		if (canOfferUniversalCoverage(cities,locations,numHospitals,result,st)) return true;
	}

	return false;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector<Set<string> >& result) {
	Vector<Set<string> > myVec;
	return canOfferUniversalCoverage(cities,locations,numHospitals,result,myVec);
}

int main() {
    Set<string> cities;
	Vector<Set<string> > locations;
    int numHospitals;
	Vector<Set<string> > result;

	int n;
	cout<<"number of cities: ";
	cin>>n;

	for (int i=0;i<n;i++) {
		string str;
		cout<<"choose "<<i+1<<"-th city name: ";
		cin>>str;
		cities.add(str);
	}

	int m;
	cout<<"number of hospitals: ";
	cin>>m;

	for (int i=0;i<m;i++) {
		int k;
		cout<<"number of "<<i+1<<"-th hospital contains cities: ";
		cin>>k;
		Set<string> loc;
		for (int j=0;j<k;j++) {
			cout<<"name of "<<j+1<<"-th city: "; 
			string str;
			cin>>str;
			loc.add(str);
		}
		locations.add(loc);
	}

	cout<<"max number of hospitals: ";
	cin>>numHospitals;

	if (canOfferUniversalCoverage(cities,locations,numHospitals,result)) {
		for (int i=0;i<result.size()-1;i++)
			cout<<result[i].toString()<<" - ";

		cout<<result[result.size()-1].toString()<<endl;
		return 0;
	}

	cout<<"impossible"<<endl;
    return 0;
}
