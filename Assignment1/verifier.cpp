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
	long long int y;
	int z;
	string f="";
	int used=transmitted.length();
	char temp[transmitted.length()];
	int i = 0;
	char new_one[generator.length()+1];
	char final[generator.length()-1];

	for (i; i <generator.length()&&i<transmitted.length(); i++)
	{
		temp[i]=transmitted[i];
		--used;

	}
	temp[i]=' ';
	i++;
	for (int k=0; k <generator.length(); k++)
	{
		temp[i]=generator[k];
		
		if(k==transmitted.length()-1)
		{
			break;
		}
		if(i>(transmitted.length()+generator.length()-1))
		{
			rem=strtoll(temp,&Pend,2);
			goto l1;
		}
		i++;
	}

	x=strtoll(temp,&Pend,2);

	y=strtoll(Pend,&Pend,2);


	z=x^y;
	
	f=bitset<32>(z).to_string();
	
	
	if(used<0||used==0)
	{
		rem=z;
		goto l1;
	}
	while(used>0)
	{
		for (int n = 0; n < 32; n++)
		{
					int count=0;

			if(f[n]=='1')
			{


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
						}
						rem=strtoll(final,&Pend,2);
						goto l1;
						break;
					}
					else
					{
						
						new_one[w]=transmitted[transmitted.length()- used];
						used--;
						count++;
					}
				}
				break;
			}
			else if(used>0&&f[n]=='0')
			{
				int zero_count=0;
				for (int y = 0; y < 32; y++)
				{
					if(f[y]=='0')
					{
						zero_count++;
					}
				}
				if(zero_count==32)
				{

					for (int j= 0; used>0&&j<generator.length(); j++)
					{
				
						new_one[j]=transmitted[transmitted.length()- used];
						used--;
						
					}
					break;
				}
				else
				{

				}
			}
			else if(used<1)
			{	
				cout<<"used<1"<<endl;
				goto l2;
				break;	
			}
			
		}
		new_one[generator.length()]=' ';
		x=strtoll(new_one,&Pend,2);
	
		z=y^x;
		x=0;
		f="";
		f=bitset<32>(z).to_string();
		
		l1:if(rem!=0||(used<1&&rem==0&&z!=0))
		{
			cout<<"it isn't correct"<<endl;
			break;
		}
		l2:if(used<1&&z==0)
		{
			cout<<"verified"<<endl;
			break;
		}
		z=0;
	}
}
