#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,num,sum,a[300],f[3000005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		sum+=a[i];
	}
	num=sum/2;
	for(int i=1;i<=n;++i)
		for(int j=num;j>=a[i];--j)
			f[j]=max(f[j],f[j-a[i]]+a[i]);
	num=f[num];
	sum=sum-num;
	cout<<abs(sum-num);
	return 0;
}
