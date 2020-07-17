#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long x,n,num=1;
	cin>>x>>n;
	for(long long i=1;i<=n;i++)
		num*=(x+1);
	cout<<num;
	return 0;
}
