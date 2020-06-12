#include "QInt.h"

QInt QInt::operator=(QInt A)
{
	a = A.a;
	b = A.b;
	full = A.full;
	return *this;
}

QInt operator+(QInt A, QInt B) // Toán tử + Giữa 2 QInt
{
	string intA = A.GetBits();
	string intB = B.GetBits();
	string sum = SumBin(intA, intB);
	QInt temp;
	if (sum == "Math ERROR!!!!!!!") // Đã tràn bits
	{
		temp.a = 0;
		temp.b = 0;
		temp.full = true;
	}
	else
		temp.SaveBits(sum);
	return temp;
}

QInt operator-(QInt A, QInt B) // Toán tử - giữa 2 QInt
{
	string intA = A.GetBits();
	string intB = B.GetBits();
	string subt = SubtBin(intA, intB);
	QInt temp;
	if (subt == "Math ERROR!!!!!!!") // Đã tràn bits
	{
		temp.a = 0;
		temp.b = 0;
		temp.full = true;
	}
	else
		temp.SaveBits(subt);
	return temp;
}

QInt operator*(QInt A, QInt B) // Toán tử * giữa 2 QInt
{
	string intA = A.GetBits();
	string intB = B.GetBits();
	string multi = MultiplyBin(intA, intB);
	QInt temp;
	if (multi == "Math ERROR!!!!!!!") // Đã tràn bits
	{
		temp.a = 0;
		temp.b = 0;
		temp.full = true;
	}
	else
		temp.SaveBits(multi);
	return temp;
}

QInt operator/(QInt A, QInt B) // Toán tử / giữa 2 QInt
{
	string intA = A.GetBits();
	string intB = B.GetBits();
	string divi = DiviBin(intA, intB);
	QInt temp;
	if (divi == "Math ERROR!!!!!!!") // Vô định hoặc lỗi gì đó
	{
		temp.a = 0;
		temp.b = 0;
		temp.full = true;
	}
	else
		temp.SaveBits(divi);
	return temp;
}

QInt operator&(QInt A, QInt B)
{
	QInt tem;
	tem.a = A.a & B.a;
	tem.b = A.b & B.b;
	return tem;
}

QInt operator|(QInt A, QInt B)
{
	QInt tem;
	tem.a = A.a | B.a;
	tem.b = A.b | B.b;
	return tem;
}

QInt operator^(QInt A, QInt B)
{
	QInt tem;
	tem.a = A.a ^ B.a;
	tem.b = A.b ^ B.b;
	return tem;
}

QInt operator~(QInt A)
{
	A.a = ~A.a;
	A.b = ~A.b;
	return A;
}


QInt QInt::operator<<(int k)
{
	long long temp;
	for (int i = 0; i < k; i++)
	{
		temp = (b >> 63) & 1ULL;
		b <<= 1;
		a <<= 1;
		a |= temp;
	}
	return *this;
}

QInt QInt::operator>>(int k)
{
	long long temp = 0;
	long long temp2 = 0;
	for (int i = 0; i < k; i++)
	{
		temp = 1ULL & a;
		temp2 = (1ULL << 63) & b;
		a >>= 1;
		b >>= 1;
		b = (b & (~(1ULL << 63))) | (temp << 63);
	}
	return *this;
}


QInt QInt::ROL()
{
	long long temp;		// 
	temp = (a >> 63ULL) & 1ULL;		// lấy bit đầu tiên của a 
	*this << 1ULL;
	b |= temp;
	return *this;
}

QInt QInt::ROR()
{
	long long temp = 0; // Neu
	temp = b & 1ULL;
	*this >> 1;
	a = (a & ~(1ULL << 63)) | (temp << 63);
	return *this;
}

bool QInt::GetFull()
{
	return full;
}

string QInt::GetBits() // Lấy dãy bit được lưu trữ. Lưu trữ số a là 64 bit đầu tiên, b là 64 bits tiếp theo
{
	int start = 0; // Lấy điểm bắt đầu, nếu start = 0 nghĩa là các bits đầu tiên = 0 nên chưa lưu trữ
	string bits;
	for (int i = 0; i < 64; i++)
	{
		if (((a >> 63 - i) & 1) == 1)
			start = 1;
		if (start == 1)
			bits.push_back(((a >> 63 - i) & 1ULL) + 48);
	}
	for (int i = 0; i < 64; i++)
	{
		if (((b >> 63 - i) & 1) == 1)
			start = 1;
		if (start == 1)
			bits.push_back(((b >> 63 - i) & 1ULL) + 48);
	}
	ChuanHoa(bits);
	return bits;
}

void QInt::SaveBits(string bits) // Lưu từ dãy bits lại
{
	ChuanHoa(bits);
	a = 0, b = 0;

	int leng = bits.length();
	if (leng < 65)
	{
		for (int i = 0; i < leng; ++i)
		{
			if ((bits[i] - 48) == 1)
			{
				b |= (1ULL << leng - i - 1);
			}
		}
		return;
	}

	int countBitA = leng - 64;

	for (int i = 0; i < 64; ++i)
	{
		if ((bits[countBitA + i] - 48) == 1)
			b |= 1ULL << 63 - i;
	}
	for (int i = 0; i < countBitA; ++i)
		if (bits[i] - 48 == 1)
			a |= 1ULL << countBitA - i - 1;
	return;
}

