#include "BigInt.h"

BigInt operator+(BigInt A, BigInt B)
{
	string intA = A.GetBits();
	string intB = B.GetBits();
	string sum = SumBin(intA, intB);
	BigInt temp;
	temp.SaveBits(sum);
	return temp;
}


void ChuanHoa(string &bits) // Chuẩn hóa chuỗi bits, xóa các số 0 đầu tiên
{
	while (bits[0] == 48)
	{
		if (bits.length() == 1)
			return;
		bits.erase(0,1);
	}
}


string BigInt::GetBits() // Lấy dãy bit được lưu trữ. Lưu trữ số a là 64 bit đầu tiên, b là 64 bits tiếp theo
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

void BigInt::SaveBits(string bits) // Lưu từ dãy bits lại
{
	cout << bits << endl;
	ChuanHoa(bits);
	cout << bits << endl;
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
		if(bits[i]-48==1)
			a |= 1ULL << countBitA - i - 1;
	return;
}

void AddBit0(string &bits, int n) // Đưa vào cho đủ n bit
{
	if (bits.length() >= n)
		return;
	while (bits.length() < n)
		bits.insert(0, "0");
}

string SumBin(string bin1, string bin2) // Cộng 2 nhị phân
{
	if (bin1.length() > bin2.length()) // Thêm bits cho bằng số phần tử nhau
		AddBit0(bin2, bin1.length());
	else
		AddBit0(bin1, bin2.length());
	int sur = 0;
	string Result;
	int sum;
	for (int i = bin1.length() - 1; i >= 0; --i)
	{
		sum = sur + bin1[i] + bin2[i] - 96;
		if (sum > 1)
		{
			sur = 1;
			Result.insert(Result.begin(), sum + 46);
		}
		else
		{
			sur = 0;
			Result.insert(Result.begin(), sum + 48);
		}
	}
	if (sur == 1)
		Result.insert(0, "1");
	if (Result.length() > 128)
		Result.erase(0, 1);
	return Result;
}

void DichTrai(string& bits, int n) // Hàm dịch trái n phần tử
{
	int leng = bits.length();
	if (n > leng)
	{
		for (int i = 0; i < leng; ++i)
			bits[i] = '0';
		return;
	}
	if (n <= 0)
		return;
	for (int i = 0; i < leng - n; ++i)
		bits[i] = bits[i + n];
	for (int i = leng - n; i < leng; ++i)
		bits[i] = '0';
}

string MultiplyBin(string bin1, string bin2)
{
	AddBit0(bin2, 128);
	AddBit0(bin1, 128);
	int leng = bin1.length();
	string result;
	int count = 0;
	for (int i = leng - 1; i >= 0; i--)
	{
		if ((bin2[i] - 48) & 1ULL) // kiểm tra từng bit của thừ số thứ 2, nếu là 1 thì dịch trái thừa số thứ nhất nếu cần rồi cộng vào kq
		{
			DichTrai(bin1, count);
			result = SumBin(result, bin1);
			count = 1;
		}
		else
			count++; // Đếm số lượng bit 0 liên tiếp để dịch trái
	}
	return result;
}

string MultiplyOneDigit(string str, int factor) // Nhân hai số cùng cơ số 
{
	if (factor < 1 || factor > 9)
		return "0";
	string result = "";
	int len = str.length();
	int rem = 0;
	int temp;
	for (int i = len - 1; i >= 0; i--)
	{
		temp = factor * (str[i] - '0') + rem;
		rem = 0;
		if (temp >= 10)
		{
			rem = temp / 10;
			temp -= rem * 10;
		}
		result.insert(0, to_string(temp));
	}
	if (rem)
		result.insert(0, to_string(rem));
	return result;
}

string PowOneDigit(int factor, int exp) // hàm lũy thừa
{
	if (exp == 0)
		return "1";
	string result = to_string(factor);
	while (--exp)
		result = MultiplyOneDigit(result, factor);
	return result;
}

string AddTwoIntString(string num1, string num2) // Cộng hai số nguyên thập phân
{
	// num1 = 12345    num2 = 678901
	int len1 = num1.size(), len2 = num2.size(), len;
	if (len1 > len2)
		num2.insert(0, len1 - len2, '0');
	if (len1 < len2)
		num1.insert(0, len2 - len1, '0');
	len = num1.size();
	int tmp, tmp1, tmp2, flag = 0;
	string result = "";
	for (int i = len - 1; i >= 0; i--)
	{
		tmp1 = num1[i] - '0';
		tmp2 = num2[i] - '0';
		tmp = tmp1 + tmp2 + flag;
		if (tmp > 9)flag = 1;
		else flag = 0;
		result = to_string(tmp % 10) + result;
	}
	if (flag == 1)
		result = '1' + result;
	return result;
}

string PositivePowTwo(int exp) // Hàm 2 mũ exp
{
	return PowOneDigit(2, exp);
}

string BinToDec(string bit)// Chuyển hệ 2 sang 10
{
	string result = "";
	int len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (bit[i] == '1')
			result = AddTwoIntString(result, PositivePowTwo(len - i - 1)); // Cộng lần lượt x*2^0 ->y*2^exp
	}
	return result;
}

string DivideStringForTwo(string str) // Chia chuỗi hệ thập phân cho 2, lấy nguyên
{
	string thuong;
	int len = str.size();
	int du = str[0] - '0', i = 0, j;
	while (i <= len - 1)
	{
		for (j = 1; j <= 10; j++)
		{
			if (2 * j > du)
			{
				thuong.append(1, j - 1 + '0');
				du = du - 2 * (j - 1);
				break;
			}
		}
		i++;
		du = du * 10 + str[i] - '0';
	}
	int pos = thuong.find_first_not_of('0');
	if (pos < 0)pos = 0;
	thuong = thuong.substr(pos, thuong.size() - pos);
	if (thuong.size() == 0)thuong += '0';
	return thuong;
}

// Chuyển từ chuỗi số nguyên lớn sang chuỗi nhị phân 128 bits
string DecToBin(string dec)
{
	string temp = dec;
	int len = temp.size();
	string bin;
	char c;
	while (temp != "0")
	{
		c = (temp[len - 1] - '0') % 2; // Lấy số dư chia 2 rồi bỏ lên đầu chuỗi
		bin.insert(0, to_string(c));
		temp = DivideStringForTwo(temp); // Chia 2 lấy nguyên
		len = temp.size();
	}
	int l = bin.length();
	if (l < 128)
		bin.insert(0, 127, '0');
	return bin;
}