#include "BigInt.h"

int main()
{
	BigInt test;
	test.SaveBits("00011110011011");
	cout << test.GetBits();
}