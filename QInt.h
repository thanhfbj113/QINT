#pragma once
#include "BigInt.h"

class QInt
{
private:
	long long a; // Lưu trữ 64 bits đầu ( bit đầu tiên là bit dấu 0: +, -: -,
	long long b; // Lưu trữ 64 bits tiếp theo

	bool full = false; // False = chưa tràn, True = Tràn

public:
	bool GetFull();

	string GetBits();
	void SaveBits(string bits);


	QInt operator=(QInt);
	friend QInt operator+(QInt, QInt);
	friend QInt operator-(QInt, QInt);
	friend QInt operator*(QInt, QInt);
	friend QInt operator/(QInt, QInt);

	friend QInt operator&(QInt A, QInt B);
	friend QInt operator|(QInt A, QInt B);
	friend QInt operator^(QInt A, QInt B);
	friend QInt operator~(QInt A);

	QInt operator<<(int k);
	QInt operator>>(int k);


	QInt ROL();
	QInt ROR();

};