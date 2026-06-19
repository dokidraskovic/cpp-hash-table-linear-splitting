#ifndef _SplitSequenceLinearHashing_h_
#define _SplitSequenceLinearHashing_h_
#include "AddressFunction.h"

class SplitSequenceLinearHashing : public AddressFunction {
	int s1;
	int s2;
public:
	SplitSequenceLinearHashing(int s11, int s22) :s1(s11), s2(s22) {}
	int getAddress(unsigned int key, int a, int i, int n) const override
	{
		if (n > 0)
			return (a + s1 * i) % n;
		else return (a + s2 * i) % abs(n);
	}
};

#endif

