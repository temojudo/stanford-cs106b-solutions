/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "gobjects.h"
using namespace std;


void drawTriangles(int n,double x0,double y0,double r,GWindow &window) {
	if (n<0) return;

	n--;
	GPoint pt1,pt2,pt3;

	pt2=window.drawPolarLine(x0,y0,r,60);
	pt3=window.drawPolarLine(pt2.getX(),pt2.getY(),r,-60);
	pt1=window.drawPolarLine(pt3.getX(),pt3.getY(),r,180);

	drawTriangles(n,pt1.getX(),pt1.getY(),r/2,window);
	drawTriangles(n,(pt1.getX()+pt2.getX())/2,(pt1.getY()+pt2.getY())/2,r/2,window);
	drawTriangles(n,(pt1.getX()+pt3.getX())/2,(pt1.getY()+pt3.getY())/2,r/2,window);

}

int main() {
	GWindow window(700,400,true);
    
	cout<<"Enter n for number of sierpinski triangels: ";
	int n;
	cin>>n;

	cout<<"Enter length of big triangle edge: ";
	double r;
	cin>>r;

	drawTriangles(n,(window.getWidth()-r)/2,window.getHeight()/2+r*sqrt(3.0)/3,r,window);
	return 0;
}
