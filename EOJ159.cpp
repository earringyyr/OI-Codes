#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long t,ma,a,b,d[10];
long long su[1000005],zhi[1000005];
long long sum;
void xian()
{
	for(long long i=2;i<=sqrt(b);++i)
	{
		if(!su[i])
		{
			su[i]=i;
			zhi[++sum]=i;
		}
		for(long long j=1;j<=sum&&zhi[j]<=su[i]&&zhi[j]*i<=sqrt(b);++j)
			su[zhi[j]*i]=zhi[j];
	}
	return;
}
int main()
{
	cin>>t;
	cin>>a>>b;
	for(long long i=1;i<=t;++i)
		cin>>d[i];
	xian();
	long long anss[10]={0};
	for(long long i=a;i<=b;++i)
	{
		long long len=i,ans[10];
		for(long long j=1;j<=t;++j)
			ans[j]=1;
		if(len<sqrt(len))
		{
			while(len!=su[len])
			{
			long long num=0;
			while(len%su[len]==0)
			{
				num++;
				len/=su[len];
			}
			for(long long tt=1;tt<=t;++tt)
				if(d[tt]!=su[len])
					ans[tt]*=num+1;
			}
		}
		else
		{
			for(long long j=1;j<=sum;++j)
			{
				if(zhi[j]>sqrt(i))
					break;
				if(len%zhi[j]==0)
				{
					long long num=0;
					while(len%zhi[j]==0)
					{
						len/=zhi[j];
						num++;
					}
					for(long long tt=1;tt<=t;++tt)
						if(zhi[j]!=d[tt])
							ans[tt]*=num+1;
				}
			}
		}
		for(long long tt=1;tt<=t;++tt)
			if(len!=1&&d[tt]!=len)
				ans[tt]*=2;
		for(long long tt=1;tt<=t;++tt)
			anss[tt]+=ans[tt];
	}
	for(long long i=1;i<=t;++i)
		cout<<anss[i]<<endl;
	return 0;
}
