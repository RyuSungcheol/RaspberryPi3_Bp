/*
 * passing.cpp
 *
 *  Created on: Jan 21, 2020
 *      Author: rpi
 */




#include <iostream>
#include <sstream>

using namespace std;

int afunction(int val, int &cr, int *ptr, int &ref){
	val+=cr;
	//cr+=val;
	*ptr+=10;
	//ref+=10;
	ref += ref;
	return val;
}

int main(){
	int a = 100, b = 200, c = 300;
	int ret;

	ret = afunction(a, a, &b, c);
	cout << "The value of a = " << a << endl;
	cout << "The value of b = " << b << endl;
	cout << "The value of c = " << c << endl;
	cout << "The return value is "<< ret <<endl;
	return 0;
}
