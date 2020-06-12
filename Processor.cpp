#include "Processor.h"
#include <vector>


void ChuanHoaData(string& data)
{
	while (data[0] == ' ')
		data.erase(0, 1);
	while (data[data.size()] == ' ')
		data.pop_back();
	for (int i = 0; i < data.size()-1; i++)
	{
		if (data[i] == ' ' and data[i + 1] == ' ')
		{
			data.erase(i, 1);
			--i;
		}
	}
	return;
}

int CountSpace(string data)
{
	int count = 0;
	int len = data.length();
	for (int i = 0; i < len; ++i)
	{
		if (data[i] = ' ')
			count++;
	}
	return count;
}

int StringToInt(string data)
{
	int result = 0;
	int len = data.length();
	for (int i = len - 1; i >= 0; --i)
	{
		result += pow(10, len - 1 - i) * (data[i] - 48);
	}
	return result;
}

string Result(int radix, string calculation, string input1, string input2) // Hàm phép tính
{
	QInt A, B;
	QInt result;
	switch (radix)
	{
		case 2:
		{
			A.SaveBits(input1);
			B.SaveBits(input2);
			break;
		}
		case 10:
		{
			string bits1 = DecToBin(input1);
			string bits2 = DecToBin(input2);
			A.SaveBits(bits1);
			B.SaveBits(bits2);
			break;
		}
		case 16: 
		{
			string bits1 = HextoBin(input1);
			string bits2 = HextoBin(input2);
			A.SaveBits(bits1);
			B.SaveBits(bits2);
			break;
		}
	}

	if (calculation == "+")
	{
		result = A + B;
	}
	else if (calculation == "-")
	{
		result = A - B;
	}
	else if (calculation == "*")
	{
		result = A * B;
	}
	else if (calculation == "/")
	{
		result = A / B;
	}
	else if (calculation == "&")
	{
		result = A & B;
	}
	else if (calculation == "|")
	{
		result = A | B;
	}
	else if (calculation == "^")
	{
		result = A ^ B;
	}

	if (result.GetFull()) // Nếu tràn hoặc vô định trả về math error
	{
		return "Math ERROR!!!!!!!";
	}
	
	switch (radix)
	{
		case 2:
		{
			return result.GetBits();
			break;
		}
		case 10:
		{
			return BinToDec(result.GetBits());
			break;
		}
		case 16:
		{
			return BintoHex(result.GetBits());
			break;
		}
	}
	return NULL;
}

string Result(int radix, string calculation, string input, int k) // Hàm dịch bits
{
	QInt A;
	QInt result;
	switch (radix)
	{
		case 2:
		{
			A.SaveBits(input);
			break;
		}
		case 10:
		{
			string bits = DecToBin(input);
			A.SaveBits(bits);
			break;
		}
		case 16:
		{
			string bits1 = HextoBin(input);
			A.SaveBits(bits1);
			break;
		}
	}

	if (calculation == "<<")
	{
		result = A << k;
	}
	else if (calculation == ">>")
	{
		result = A >> k;
	}

	switch (radix)
	{
		case 2:
		{
			return result.GetBits();
			break;
		}
		case 10:
		{
			return BinToDec(result.GetBits());
			break;
		}
		case 16:
		{
			return BintoHex(result.GetBits());
			break;
		}
	}
	return NULL;
}

string Result(int radix, int radix2, string input) // Hàm đổi cơ số
{
	QInt result;
	switch (radix) // Lưu input theo đúng cơ số ban đầu
	{
		case 2:
		{
			result.SaveBits(input);
			break;
		}
		case 10:
		{
			string bits = DecToBin(input);
			result.SaveBits(bits);
			break;
		}
		case 16:
		{
			string bits1 = HextoBin(input);
			result.SaveBits(bits1);
			break;
		}
	}
	switch (radix2) // Xuất ra cơ số yêu cầu
	{
		case 2:
		{
			return result.GetBits();
			break;
		}
		case 10:
		{
			return BinToDec(result.GetBits());
			break;
		}
		case 16:
		{
			return BintoHex(result.GetBits());
			break;
		}
	}
	return NULL;
}

string Result(int radix, string calculation, string input) // Hàm rol ror và ~
{
	QInt result;
	switch (radix) // Lưu input theo đúng cơ số ban đầu
	{
		case 2:
		{
			result.SaveBits(input);
			break;
		}
		case 10:
		{
			string bits = DecToBin(input);
			result.SaveBits(bits);
			break;
		}
		case 16:
		{
			string bits1 = HextoBin(input);
			result.SaveBits(bits1);
			break;
		}
	}
	if (calculation == "~")
	{
		result = ~result;
	}
	else if (calculation == "ror")
	{
		result.ROR();
	}
	else if (calculation == "rol")
	{
		result.ROL();
	}

	switch (radix) // Xuất ra cơ số yêu cầu
	{
		case 2:
		{
			return result.GetBits();
			break;
		}
		case 10:
		{
			return BinToDec(result.GetBits());
			break;
		}
		case 16:
		{
			return BintoHex(result.GetBits());
			break;
		}
	}
	return NULL;
}


string ProcessLine(string data)
{
	ChuanHoaData(data);
	string result;
	vector <string> inp;

	while (!data.empty())
	{
		inp.push_back(data.substr(0, data.find(" ")));
		if (data.find(" ") > data.size()) // Hết khoảng trắng 
		{
			break;
		}
		else
		{
			data.erase(0, data.find(" ") + 1); // Xóa đi chuỗi vừa lấy
		}
	}
	for (int i = 0; i < inp.size(); i++)
	{
		ChuanHoa(inp[i]);
	}
	if (inp.size() == 4)
	{
		int radix = StringToInt(inp[0]);
		if (inp[2] == ">>" || inp[2] == "<<") // Dịch trái và phải
		{
			int k = StringToInt(inp[3]);
			result = Result(radix, inp[2], inp[1], k);
		}
		else // Các phép toán + - * / & | ^
		{
			result = Result(radix, inp[2], inp[1], inp[3]);
		}
	}
	else if (inp.size() == 3)
	{
		int radix = StringToInt(inp[0]);
		if (inp[1] == "2" || inp[1] == "10" || inp[1] == "16") // Đổi cơ số
		{
			int radix2 = StringToInt(inp[1]);
			result = Result(radix, radix2, inp[2]);
		}
		else
		{
			result = Result(radix, inp[1], inp[2]);
		}
	}

	return result;
}

void Processor(ifstream& input, ofstream& output)
{
	while (!input.eof())
	{
		string line;
		getline(input, line);
		output << ProcessLine(line) << endl;
	}
	return;
}