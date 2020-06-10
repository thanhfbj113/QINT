#pragma once
#include <iostream>
#include <string>
using namespace std;

class BigInt
{
private:
	long long a; // Lưu trữ 64 bits đầu ( bit đầu tiên là bit dấu 0: +, -: -,
	long long b; // Lưu trữ 64 bits tiếp theo

	bool full = false; // False = chưa tràn, True = Tràn

public:
	string GetBits();
	void SaveBits(string bits);

	string outDec();

	
	friend BigInt operator+(BigInt, BigInt);
	friend BigInt operator-(BigInt, BigInt);
	friend BigInt operator*(BigInt, BigInt);
	friend BigInt operator/(BigInt, BigInt);
};

void ChuanHoa(string &bits);
void AddBit0(string &bits, int n);
string SumBin(string bin1, string bin2);
string SubtBin(string bin1, string bin2);
string MultiplyBin(string bin1, string bin2);
string Bu2(string bin);
string DiviBin(string bin1, string bin2);


string DecToBin(string dec);
string BinToDec(string bit);

string BintoHex(string bin);
string HextoBin(string hex);

string DectoHex(string dec);
string HextoDec(string hex);