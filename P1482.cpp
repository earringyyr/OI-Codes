#include<iostream>
#include<cstdio>
using namespace std;
int gongyue(int a,int b)
{
	if(a%b==0)
		return b;
	return gongyue(b,a%b);
}
int main()
{
	char e;
	int a,b,c,d;
	cin>>a>>e>>b>>c>>e>>d;
	a*=c;
	b*=d;
	int len=gongyue(a,b);
	a/=len;
	b/=len;
	cout<<b<<" "<<a;
	return 0;
}
