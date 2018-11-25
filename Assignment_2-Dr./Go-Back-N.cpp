#include <iostream>
#include<string>
#include<string.h>
using namespace std;

struct packet
{
	char info;
	int seq, ack;
};
string physical_layer(int &index, string input)
{
	input[index] = 'E';
	return input;
	cout << input << endl;
}
void Go_back_N(string input, int size ,int &index)
{
	string buffer = physical_layer(index, input);
	char reciever;
	int timer = 0, time = 0;
	int nextframe = 0, lost_frame; //frame to transmit
	while (nextframe <size)
	{
		reciever = buffer[nextframe];
		if (reciever != 'E' && timer == 0)
		{
			cout << "at time: " << time << "  " << reciever << "  is recieved" << endl << "\n";
			nextframe++;
			time++;
			cout << "at time: " << time << "  " << reciever << "  is acknoledged" << endl << "\n";
			//time++;
		}
		else if (reciever == 'E')
		{
			lost_frame = nextframe;
			//cout << buffer[lost_frame]<<endl;
			nextframe++;
			cout << "at time: " << time << "  error frame " << endl ;
			time++;
			timer++;
		}
		else
		{
			cout << "at time: " << time << "  " << reciever << "  frame discarded " << endl << endl;
			nextframe++;
			time++;
			timer++;
		}
		if (timer == 4)
		{
			timer = 0;
			nextframe = lost_frame;
			buffer[nextframe] = input[nextframe];
			cout << "at time: " << time << "  " << buffer[nextframe] << "  acknowlegement timeout , it will be retransmitted" << endl << endl;
		}
	}
}
int main()
{
	string input;
	cout << "Enter the transmitted data bits" << endl;
	cin >> input;
	int error_bit;
	cout << "Enter bit's location you want to be damaged" << endl;
	cin >> error_bit;
	physical_layer(error_bit, input);
	Go_back_N(input, input.length(),error_bit);
	system("pause");
}
