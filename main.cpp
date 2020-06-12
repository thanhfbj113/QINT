#include "Processor.h"

int main(int argc, char** argv)
{
	ifstream inputFile;
	ofstream outputFile;
	if (argc < 3)
	{
		cout << "Khong nhan dung du lieu!" << endl;
		return 0;
	}

	inputFile.open(argv[1]);
	outputFile.open(argv[2]);
	if (!inputFile.is_open())
		cout << "Link input khong chinh xac!" << endl;
	if (!outputFile.is_open())
		cout << "Link output khong chinh xac!" << endl;
	cout << argv[1] << endl;
	cout << argv[2] << endl;

	Processor(inputFile, outputFile);

	inputFile.close();
	outputFile.close();

	return 0;

	//cout << ProcessLine("2 ror 1110011101");

	/*QInt test;
	string temp1 = "1110011101";
	string temp2= "0";
	cout << HextoBin("954DCB") << endl;
	cout << BintoHex("1101101001110001101001");*/

	//cout << BinToDec("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100") << endl;

}