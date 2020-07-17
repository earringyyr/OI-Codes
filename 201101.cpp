#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	char n[20];
	bool pan=false;
	gets(n);
	if(n[0]=='-')
	{
		cout<<'-';
		for(int i=strlen(n)-1;i>=1;i--)
		{
			if(!pan&&n[i]!='0')
				pan=true;
			if(pan)
			{
				cout<<n[i];
			}
		}
	}
	else
	{
		for(int i=strlen(n)-1;i>=0;i--)
		{
			if(!pan&&n[i]!='0')
				pan=true;
			if(pan)
			{
				cout<<n[i];
			}
		}
	}
	return 0;
}
