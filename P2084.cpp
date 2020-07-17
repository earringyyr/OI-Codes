#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int m;
	char n[1001];
	cin>>m;
	scanf("%s",n);
	int len;
	for(int i=strlen(n)-1;i>=0;--i)
		if(n[i]!='0')
		{
			len=i;
			break;
		}
	for(int i=0;i<strlen(n);++i)
		if(n[i]!='0')
		{
			cout<<n[i]<<"*"<<m<<"^"<<strlen(n)-i-1;
			if(i<len)	
				cout<<"+";
		}
	return 0;
}
