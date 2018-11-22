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

void verifier (string &frame, string &Generator)
{
	string  Zeros,newFrame, Temp, rubishFrame;
	int appendedZeros = Generator.length() - 1;
	for (int z = 0; z < appendedZeros; z++)
	{
		Zeros += "0";
	}
	newFrame = frame;
	for (int i = 0; i < newFrame.length()- appendedZeros; i++)
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
	if (rubishFrame == Zeros)
	{
		cout << "Message Verified" << endl;
	}
	else
		cout << "Message not Verified" << endl;
}
