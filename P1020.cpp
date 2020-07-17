#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int n=0,b[100001],f[100001]={0};
	memset(f,0x7f,sizeof(f));
	while(cin>>b[++n]);
	n--;
	int sum=0;
	for(int i=1;i<=n;++i)
	{
		int l=1,r=sum;
		if(b[i]<=f[sum])
			f[++sum]=b[i];
		else
		{
			while(l<r)
			{
				int mid=(l+r)/2;
				if(f[mid]<b[i])
					r=mid;
				else
					l=mid+1;
			}
			f[l]=b[i];
		}
	}
	cout<<sum<<endl;
	memset(f,0,sizeof(f));
	sum=0;
	for(int i=1;i<=n;++i)
	{
		int l=1,r=sum;
		if(b[i]>f[sum])
			f[++sum]=b[i];
		else
		{
			while(l<r)
			{
				int mid=(l+r)/2;
				if(f[mid]>=b[i])
					r=mid;
				else
					l=mid+1;
			}
			f[l]=b[i];
		}
	}
	cout<<sum;
	return 0;
}
