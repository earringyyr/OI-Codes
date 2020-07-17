#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[10000005];
int main()
{
	scanf("%s",a);
	if(strlen(a)<=3)
	{
		cout<<"No";
		return 0;
	}
	int num=0,p=1;
	if(a[0]=='0')
		num++;
	if(a[1]=='0')
		num++;
	if(a[2]=='0')
		num++;
	if(a[3]=='0')
		num++;
	if(num<2)
	{
		cout<<"Yes";
		return 0;
	} 
	for(int i=4;i<strlen(a);++i)
	{
		if(a[i-4]=='0')
			num--;
		if(a[i]=='0')
			num++;
		if(num<2)
		{
			p=0;
			break;
		}
	}
	if(p==0)
		cout<<"Yes";
	else
		cout<<"No";
	return 0;
}
