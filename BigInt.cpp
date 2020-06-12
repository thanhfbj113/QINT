#include "BigInt.h"



void ChuanHoa(string &bits) // Chuẩn hóa chuỗi bits, xóa các số 0 đầu tiên
{
	while (bits[0] == 48)
	{
		if (bits.length() == 1)
			return;
		bits.erase(0,1);
	}
}


void AddBit0(string &bits, int n) // Đưa vào cho đủ n bit
{
	if (bits.length() >= n)
		return;
	while (bits.length() < n)
		bits.insert(0, "0");
}

string SumBin(string bin1, string bin2) // Cộng 2 nhị phân (Tràn bits báo lỗi)
{
	bool sign = false;
	if (bin1.length() == 128 && bin2.length() == 128)
	{
		bin1 = Bu2(bin1);
		bin2 = Bu2(bin2);
		sign = 1;
	}
	if (bin1.length() > bin2.length()) // Thêm bits cho bằng số phần tử nhau
		AddBit0(bin2, bin1.length());
	else
		AddBit0(bin1, bin2.length());
	int rem = 0; // Số dư
	string result;
	int sum;
	for (int i = bin1.length() - 1; i >= 0; --i)
	{
		sum = rem + bin1[i] + bin2[i] - 96;
		if (sum > 1)
		{
			rem = 1;
			result.insert(result.begin(), sum + 46);
		}
		else
		{
			rem = 0;
			result.insert(result.begin(), sum + 48);
		}
	}
	if (rem == 1)
		result.insert(0, "1");
	if (result.length() > 128 && bin1.length() == 128 && bin1[0] == bin2[0]) // Nếu tràn bits thì trả về MATH ERROR
		result = "Math ERROR!!!!!!!"; // Lớn hơn 16 bytes để tránh trùng với lưu trữ
	if (result.length() > 128)
		result.erase(0, 1);
	ChuanHoa(result);
	if (sign)
		result = Bu2(result);
	return result;
}

string SumBin(string bin1, string bin2, int maxlen) // Cộng 2 nhị phân (Tràn bits tự bỏ đầu, giới hạn là max len)
{
	if (bin1.length() > bin2.length()) // Thêm bits cho bằng số phần tử nhau
		AddBit0(bin2, bin1.length());
	else
		AddBit0(bin1, bin2.length());
	int sur = 0; // Số dư
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
	while (Result.length() > maxlen)
		Result.erase(0, 1);
	ChuanHoa(Result);
	return Result;
}

string Bu2(string bin)
{
	AddBit0(bin, 128);
	string bu1;
	string bu2;
	string so1 = "1";
	int du = 0, sum;
	for (int i = 0; i < 128; ++i) 
	{
		bu1.push_back(((bin[i] - 48) ^ 1) + 48);// Tạo bù 1
	}
	bu2 = SumBin(bu1, so1, 128);
	ChuanHoa(bu2);
	return bu2;
}

string SubtBin(string bin1, string bin2) //Trừ hai số nhị phân, (bin1-bin2)
{
	string bu2 = Bu2(bin2);
	return SumBin(bin1, bu2);
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

string MultiplyBin(string bin1, string bin2) // Nhân hai số nhị phân
{
	bool sign = false;
	if (bin1.length() == 128)
	{
		bin1 = Bu2(bin1);
		sign ^= 1;
	}
	if (bin2.length() == 128)
	{
		bin2 = Bu2(bin2);
		sign ^= 1;
	}
	AddBit0(bin2, 256);
	AddBit0(bin1, 256);
	int leng = bin1.length();
	string result;
	int count = 0;
	for (int i = leng - 1; i >= 0; i--)
	{
		if ((bin2[i] - 48) & 1ULL) // kiểm tra từng bit của thừ số thứ 2, nếu là 1 thì dịch trái thừa số thứ nhất nếu cần rồi cộng vào kq
		{
			DichTrai(bin1, count);
			result = SumBin(result, bin1,256);
			count = 1;
		}
		else
			count++; // Đếm số lượng bit 0 liên tiếp để dịch trái
	}
	ChuanHoa(result);
	
	if (sign) // Kiểm tra các dấu của số ban đầu
		result = Bu2(result);

	if(result.length()>128)
		result = "Math ERROR!!!!!!!"; // Lớn hơn 16 bytes để tránh trùng với lưu trữ
	return result;
}

string DiviBin(string bin1, string bin2) // Chia lấy phần nguyên hệ nhị phân, bin1 là số chia, bin2 là số bị chia
{
	if (bin2 == "0")
		return "Math ERROR!!!!!!!";
	bool sign = false;
	if (bin1.length() == 128)
	{
		sign ^= 1;
		bin1 = Bu2(bin1); // đổi ra số dương
	}
	if (bin2.length() == 128)
	{
		sign ^= 1;
		bin2 = Bu2(bin2); // đổi ra số dương
	}
	ChuanHoa(bin1);
	ChuanHoa(bin2);
	string result;
	string rem;
	int len = bin1.length();
	for (int i = 0; i < len; ++i)
	{
		rem += bin1[i];
		if (SubtBin(rem, bin2).length() < 128)
		{
			result += "1";
			rem = SubtBin(rem, bin2);
		}
		else
		{
			result += "0";
		}
	}

	ChuanHoa(result);
	if (sign)
	{
		result = Bu2(result);
	}
	return result;
}

string MultiplyOneDigit(string str, int factor) // Nhân với số có một chữ số (hệ thập phân)
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

string PowOneDigit(int factor, int exp) // hàm lũy thừa với số mũ một chữ số
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

string BinToDec(string bit)// Chuyển hệ 2 sang 10 tối đa 128 bit
{
	string result = "";
	ChuanHoa(bit);
	bool sign = false; // Mạc định là số dương
	int len = bit.length();
	if (len == 128) // Nếu là số âm
	{
		bit = Bu2(bit);
		sign ^= 1; // bit dấu là âm
	}

	len = bit.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (bit[i] == '1')
			result = AddTwoIntString(result, PositivePowTwo(len - i - 1)); // Cộng lần lượt x*2^0 ->y*2^exp
	}
	if (sign == true)
	{
		result.insert(0, "-");
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
	bool sign = false; // Mạc định là số dương
	while (dec[0] < 48 || dec[0]>57) 
	{
		if (dec[0] == '-')
			sign ^= 1;
		dec.erase(0, 1);
	}
	int len = dec.size();
	string bin;
	char c;
	while (dec != "0")
	{
		c = (dec[len - 1] - '0') % 2; // Lấy số dư chia 2 rồi bỏ lên đầu chuỗi
		bin.insert(0, to_string(c));
		dec = DivideStringForTwo(dec); // Chia 2 lấy nguyên
		len = dec.size();
	}
	if (sign == true)
		return Bu2(bin);
	return bin;
}

int Get4bits(string bin, int pos)// Đưa vào vị trí lấy ra 4 ký tự nhị phân và trả về thập phân
{
	if (bin.length() - pos < 4)
		return 0;
	int result = 0;
	for (int i = pos, j = 3; i < pos + 4; ++i, --j)
	{
		result += (bin[i] - 48)*pow(2, j);
	}
	return result;
}

string BintoHex(string bin)
{
	string result = "0";
	int count = (bin.length() + 3) / 4 * 4;
	AddBit0(bin, count);
	for (int i = 0; i < count; i += 4)
	{
		int hex = Get4bits(bin, i);
		if (Get4bits(bin, i) < 10)
		{
			result += hex + 48;
		}
		else
		{
			result += hex + 55; // Nếu từ 10-15 thì +55 để được 65-70 (A-F)
		}
	}
	ChuanHoa(result);
	return result;
}

string To4bits(int x) // Đưa vào 1 số nguyên từ 0 -> 15 trả về nhị phân
{
	string result;
	for (int i = 3; i >= 0; --i)
	{
		result += ((x >> i) & 1ULL) + 48;
	}
	return result;
}

string HextoBin(string hex)
{
	string result;
	int len = hex.length();
	for (int i = 0; i < len; ++i)
	{
		int bin = hex[i];
		if (bin > 64)
		{
			result += To4bits(bin - 55);
		}
		else
		{
			result += To4bits(bin - 48);
		}
	}
	ChuanHoa(result);
	return result;
}

string DectoHex(string dec)
{
	string bin = DecToBin(dec);
	return BintoHex(bin);
}

string HextoDec(string hex)
{
	string bin = HextoBin(hex);
	return BinToDec(bin);
}


