#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <bitset>

using namespace std;
void verifier(string transmitted,string generator);
int main()
{
	string data="",generator="";

	ifstream infile("/home/fatema/Desktop/network/file.txt");
	if(!infile.bad())
	{
		infile>>data>>generator;

	}
	verifier(data,generator);

}

void verifier(string transmitted,string generator)
{
	char * Pend;
	long long int rem=0;
	long long int x;
	int used=transmitted.length();
	char temp[transmitted.length()];
	int i = 0;
	char new_one[generator.length()+1];
	char final[generator.length()-1];

	for (i; i <generator.length(); ++i)
	{
		temp[i]=transmitted[i];
		used--;
		cout<<used<<endl;
	}
	temp[i]=' ';
	i++;
	for (int k=0; k <generator.length(); ++k)
	{
		temp[i]=generator[k];
		i++;
	}

	x=strtoll(temp,&Pend,2);
	long long int y=strtoll(Pend,&Pend,2);

	cout<<x<<endl<<y<<endl;

	int z=x^y;
	
	string f=bitset<32>(z).to_string();
	
	cout<<z<<endl<<f<<endl;
	
	while(used>0)
	{
		cout<<"iam here"<<endl;
		for (int n = 0; n < 32; n++)
		{
					cout<<"iam here1"<<endl;

			if(f[n]=='1')
			{
						cout<<"iam here2"<<endl;
						int count=0;


				for (int w = 0; w < generator.length(); ++w)
				{
					
					if(n<32)
					{
						new_one[w]=f[n];
						cout<<new_one[w]<<'*'<<endl;
						count++;
						n++;
					}
					else if(used<1)
					{
						for (int l = 0; l < count; l++)
						{
							final[l]=new_one[l+1];
							cout<<"gg"<<count<<endl;
						}
						rem=strtoll(final,&Pend,2);
						cout<<"re"<<rem<<endl;
						goto l1;
						break;
					}
					else
					{
						
						new_one[w]=transmitted[transmitted.length()- used];
						cout<<new_one[w]<<"PP"<<endl;
						used--;
						count++;
					}
				}
				break;
			}
			else if(f[n]=='0'&&n>31&&used>0)
			{
				cout<<"iam 4"<<endl;
				for (int w = 0; w < generator.length(); ++w)
				{
					
						new_one[w]=transmitted[used];
						used--;
					
				}
				break;
			}
			else if(used<1)
			{
				goto l2;
			}
			
		}
		new_one[generator.length()]=' ';
		x=strtoll(new_one,&Pend,2);
	
		cout<<x<<endl<<y<<endl;
		z=y^x;
		f="";
		f=bitset<32>(z).to_string();
		cout<<z<<endl<<f<<endl;
		l1:if(rem!=0)
		{
			cout<<"it isn't correct"<<endl;
			break;
		}
		l2:if(rem==0&&used<1)
		{
			cout<<"verified"<<endl;
			break;
		}
		
	}
}
