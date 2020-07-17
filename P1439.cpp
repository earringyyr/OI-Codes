#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int k,n,a[100001],b[100001],f[100001]={0};
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>k;
		a[k]=i;
	}
	for(int i=1;i<=n;++i)
	{
		cin>>k;
		b[i]=a[k];
	}
	int sum=0;
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
