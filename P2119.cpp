#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,num,x[40005],a[15005],b[15005],c[15005],d[15005],sum[40005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		cin>>x[i];
		sum[x[i]]++;
	}
	for(int i=1;9*i<n;++i)
	{
		num=0;
		for(int j=i*9+2;j<=n;++j)
		{
			num+=sum[j-7*i-1]*sum[j-9*i-1];
			c[j-i]+=sum[j]*num;
			d[j]+=sum[j-i]*num;
		}
		num=0;
		for(int j=n-9*i-1;j>=1;--j)
		{
			num+=sum[j+8*i+1]*sum[j+9*i+1];
			a[j]+=sum[j+2*i]*num;
			b[j+2*i]+=sum[j]*num;
		}
	} 
	for(int i=1;i<=m;++i)
		cout<<a[x[i]]<<" "<<b[x[i]]<<" "<<c[x[i]]<<" "<<d[x[i]]<<endl;
	return 0;
}
