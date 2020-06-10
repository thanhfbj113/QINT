#pragma once
#include <iostream>
#include <string>
using namespace std;

class BigInt
{
private:
	long long a;
	long long b;

public:
	string GetBits();
	void SaveBits(string bits);

	friend BigInt operator+(BigInt, BigInt);
	friend BigInt operator-(BigInt, BigInt);
};

void ChuanHoa(string &bits);
void AddBit0(string &bits, int n);
string SumBin(string bin1, string bin2);


string DecToBin(string dec);
string BinToDec(string bit);