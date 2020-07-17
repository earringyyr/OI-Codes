#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int m;
	unsigned long long ji=0,ou=1; 
	cin>>m;
	if(m==0)
	{
		cout<<1;
		return 0;
	}
	if(m==1||m==2)
	{
		cout<<m;
		return 0;
	}
	for(int i=3;i<=m;i++)
	{
		unsigned long long a=ji,b=ou;
		ji=b; 
		ou=a+b;
	}
	cout<<ji+ou;
	
} 
