#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		cout<<(n-sum)/(m-i+1)<<" ";
		sum+=(n-sum)/(m-i+1);
	}
	return 0;
} 
