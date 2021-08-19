#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<ctime>
using namespace std;
int main()
{
	srand(time(NULL));
	ofstream file("fuzzer.txt");
	string n = "";
	char ch;
	int m=1;
	cout<<"enter the maxx fuzzword input : ";
	int max;
	cin>>max;
	system("cls");
	for(int i =  0; i <m;i++)
	{
		ch= rand() %  127;
		n +=ch;
		//m++;
		if(i == m-1)
		{
			file<<n<<"\n-------------------------------\n";
			//cout<<n<<endl;
			if(m == max)
			{
				break;
			}
			m++;
			i=-1;			
			n="";
		}		
	}
	if(file.is_open())
	{
		file.close();
		cout<<"fuzzer file created";
		
	}	
}
