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
void generator(string &frame, string &Generator )
{
	string Zeros, newFrame, Temp, rubishFrame;
	int appendedZeros = Generator.length() - 1;
	for (int z = 0; z < appendedZeros; z++)
	{
		Zeros += "0";		
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
	//frame = frame.substr(0, frame.length());
	frame = frame + rubishFrame;

	ofstream outFile("output.txt");
	cout << "Open the (output.txt) file in the same location of the exe folder" << endl;
	if (outFile.is_open())
	{
		outFile << "Tranmitted : " << frame << '\n';
		outFile.close();
	}
	else cout << "Unable to open file";
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
void alter(string &frame,int bit)
{
	if (frame[bit] == '1')
	{
		frame[bit] = '0';
	}
	else if (frame[bit] == '0')
	{
		frame[bit] = '1';
	}
}
int main()
{
	string frame, Generator;
	string path;
	int bit;
	char choice;
	cout << "Enter input file Path then press Enter" << endl;
	getline(cin, path);
	cout << "Choose '1' for verification only or '2' for alter" << endl;
	cin >> choice;
	ifstream inFile(path);
	if (inFile.is_open())
	{
		switch (choice) {
		case '1':
		{
			(getline(inFile, frame)); //Read the frame from 1st line of the input file
			(getline(inFile, Generator)); //Read the generator from 2nd line of the input file
			generator(frame, Generator);
			cout << "transmitted frame : " << frame << endl;
			verifier(frame, Generator);
			inFile.close();
			break;
		}
		case'2':
		{
			(getline(inFile, frame)); //Read the frame from 1st line of the input file
			(getline(inFile, Generator)); //Read the generator from 2nd line of the input file
			generator(frame, Generator);
			cout << "transmitted frame : " << frame << endl;
			verifier(frame, Generator);
			cout << "Enter bit location you want to alter then press Enter" << endl;
			cin >> bit;
			alter(frame, bit);
			cout << "frame with altered bit : " << frame << endl;
			verifier(frame, Generator);
			inFile.close();
		}
		}
	}
	else cout << "Unable to open file";
	
	system("pause");
	return 0;
}
