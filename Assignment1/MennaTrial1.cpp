#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include <algorithm>
using namespace std;
string XOR_Function(char x ,char y)
{
	string XORvalue;
	switch (x)
	{
	case '0':
		if (y == '0')
		{
			XORvalue += '0';
			break;
		}
		else
		{
			XORvalue += '1';
			break;
		}
	case '1':
		if (y == '1')
		{
			XORvalue += '0';
			break;
		}
		else
		{
			XORvalue += '1';
			break;
		}

	default:
		break;
	}
	return XORvalue;
}
int main()
{
	string frame , generator , message , Zeros , newFrame , transmittedFrame , XORvalue , Temp;
	int quotient;
	
	ifstream inFile("input.txt");
	if (inFile.is_open())
	{
		while (getline(inFile, frame))
		{
			while (getline(inFile, generator))
			{
				int appendedZeros = generator.length() - 1;
				for (int i = 0; i < appendedZeros; i++)
				{
					Zeros = Zeros + "0";
				}
				newFrame = frame + Zeros;
				for (int m = 0; m < newFrame.length(); m++)
				{
					for (int y = 0; y < generator.length(); y++)
					{
						transmittedFrame = newFrame.substr(0, generator.length());
						XORvalue += XOR_Function(transmittedFrame[y], generator[y]);
					}
					size_t pos = XORvalue.find('1');
					if (pos == true)
					{
						for (int x = 0; x < XORvalue.length(); x++)
						{
							Temp = XORvalue.substr(XORvalue.find('1'), XORvalue.length());
						}
					}
					else // all xor result is zeros
					{
						Temp = "";
						pos = generator.length();
						Temp = Temp + newFrame[generator.length() + pos];
					}
					cout << Temp << endl;
					Temp = Temp + newFrame[generator.length() + pos];
					cout << Temp << endl;
					XORvalue = "";
					for (int r = 0; r < Temp.length(); r++)
					{
						XORvalue += XOR_Function(Temp[r], generator[r]);
					}
					cout << XORvalue << endl;
				}
			}
		}
		inFile.close();
	}
	else cout << "Unable to open file";
	ofstream outFile("output.txt");
	if (outFile.is_open())
	{
		outFile <<"FrameWithZeros: "<< newFrame << '\n';
		outFile << "goz2 mn el frame 3la ad el generator: " <<transmittedFrame << '\n';
		outFile << "Generator:"<<generator << '\n';
		outFile << "XOR: "<< XORvalue << '\n';
		outFile << "Remainder: " << Temp << '\n';
		outFile.close();
	}
	else cout << "Unable to open file";
	
	system("pause");
	return 0;
}
