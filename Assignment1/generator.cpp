#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
using namespace std;
char XOR_Function(char x, char y)
{
	switch (x)
	{
	case '0':
		if (y == '0')
		{
			return '0';
		}
		else
		{
			return '1';
		}
	case '1':
		if (y == '1')
		{
			return '0';
		}
		else
		{
			return '1';
		}
	default:
		break;
	}
}
string generator(string frame, string Generator)
{
	string Zeros, newFrame, transmittedFrame, Temp, rubishFrame;
	int appendedZeros = Generator.length() - 1;
	for (int z = 0; z < appendedZeros; z++)
	{
		Zeros = Zeros + "0";
	}
	newFrame = frame + Zeros;
	for (int i = 0; i < frame.length(); i++)
	{
		Temp = newFrame.substr(i, Generator.length());
		if (Temp[0] == '0')
			continue;
		for (int j = 0; j < Generator.length(); j++)
		{
			Temp[j] = XOR_Function(Temp[j], Generator[j]);
			newFrame[i + j] = Temp[j];
		}
	}
	rubishFrame = newFrame.substr((newFrame.length() - appendedZeros), appendedZeros);
	transmittedFrame = frame + rubishFrame;
	return transmittedFrame;
}
int main()
{
	string frame, Generator, transmittedFrame;
	ifstream inFile("D:\\Menna\\4th Elerctrical 1st Term\\Subjects\\Networks\\Assignments\\Assignment1\\input.txt");
	if (inFile.is_open())
	{
		(getline(inFile, frame)); //Read the frame from 1st line of the input file
		(getline(inFile, Generator)); //Read the generator from 2nd line of the input file
		transmittedFrame = generator(frame, Generator);
		inFile.close();
	}
	else cout << "Unable to open file";
	ofstream outFile("D:\\Menna\\4th Elerctrical 1st Term\\Subjects\\Networks\\Assignments\\Assignment1\\output.txt");
	if (outFile.is_open())
	{
		outFile <<"Tranmitted : "<<  transmittedFrame << '\n';
		outFile.close();
	}
	else cout << "Unable to open file";
	system("pause");
	return 0;
}
