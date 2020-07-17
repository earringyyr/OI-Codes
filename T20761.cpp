#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int k,l;
	long long num=1,sum=0;
	cin>>k>>l;
	for(int i=1;i<=l;i++)
	{
		sum+=num;
		num+=k;
	}
	cout<<sum;
	return 0;
} 
