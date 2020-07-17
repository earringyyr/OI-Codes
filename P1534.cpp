#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,sum=0,num=0;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int a,b;
		cin>>a>>b;
		num=num+a+b-8;
		sum+=num;
	}
	cout<<sum;
	return 0;
}
