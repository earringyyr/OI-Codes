#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int n,m,a[10001];
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=m;++i)
	{
		int len;
		for(int j=n;j>=1;--j)
			if(a[j-1]<a[j]) 
			{
				len=j-1;
				break;
			}
		int kk,k=a[len];
		sort(a+len,a+n+1);
		for(int j=len;j<=n;++j)
			if(a[j]==k)
			{
				kk=a[len];
				a[len]=a[j+1];
				a[j+1]=kk;
				break;
			}
		sort(a+len+1,a+n+1);
	}
	for(int i=1;i<=n;++i)
		cout<<a[i]<<" ";
	return 0;
} 
