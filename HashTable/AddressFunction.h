#ifndef _AddressFunction_h_
#define _AddressFunction_h_
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class AddressFunction {
public:
	virtual int getAddress(unsigned int key, int a, int i, int n) const = 0;
};

#endif

