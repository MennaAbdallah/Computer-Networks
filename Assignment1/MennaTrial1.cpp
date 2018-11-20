#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include <functional> 
#include <bitset>
using namespace std;
int main()
{
	string frame , generator , message , Zeros , newFrame , transmittedFrame , XORvalue;
	int quotient;
	bitset<5>F;
	bitset<5>G;
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
				for (int x = 0; x < frame.length(); x++)
				{
					for (int y = 0; y < generator.length(); y++)
					{
						transmittedFrame = newFrame.substr(x, generator.length());
						//XORvalue = stoi(transmittedFrame,nullptr, 2) ^ stoi(generator, nullptr, 2);
						//int integerValueG = stoi(generator, nullptr, 2);

						bitset<5>G(generator.c_str()[y]);
						cout << G << '\n'; //10011
					}
					bitset<5>F(transmittedFrame.c_str()[x]);
					cout << F << '\n'; //10000
				}
				cout << G << '\n'; //10011
				cout << F << '\n'; //10000
				XORvalue = (F ^ G).to_string();
				
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
		outFile.close();
	}
	else cout << "Unable to open file";
	
	system("pause");
	return 0;
}
