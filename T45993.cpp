#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,sum,a[200005],num[400005];
long long ans;
int main()
{
	cin>>n>>m;
	for(long long i=1;i<=n;++i)
	{
		cin>>a[i];
		num[++sum]=i-a[i];
		num[++sum]=i+a[i];
	}
	sort(num+1,num+sum+1);
	long long nu=0;
	for(long long i=1;i<=sum;++i)
	{
		if(num[i]!=num[i-1])
		{
			ans+=nu*(nu-1)/2;
			nu=0;
		}
		nu++;
	}
	ans+=nu*(nu-1)/2;
	cout<<ans;
	return 0;
}
