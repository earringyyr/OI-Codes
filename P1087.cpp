#include<iostream>
#include<cstdio>
using namespace std;
int n,num=0;
char a[10000],b[10000];
void naive(int c,int d)
{
	if(c<d)
	{
		int pan=1;
		char k=a[c];
		for(int i=c+1;i<=d;i++)
			if(a[i]!=k)
			{
				pan=0;
				break;
			}
		if(pan==0)
			b[++num]='F';
		else
			if(k=='0')
				b[++num]='B';
			else
				b[++num]='I';
		naive((c+d)/2+1,d);
		naive(c,(c+d)/2);
	}
	if(c==d)
	{
		if(a[c]=='0')
			b[++num]='B';
		else
			b[++num]='I';
	}
	return;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n;
	n=1<<n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	naive(1,n);
	for(int i=num;i>=1;i--)
		cout<<b[i];
	return 0;
}
