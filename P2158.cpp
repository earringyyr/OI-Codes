#include<iostream>
#include<cstdio>
using namespace std;
int n,sum,ans,zhi[40005],shu[40005],phi[40005];
int main()
{
	cin>>n;
	if(n==1)
	{
		cout<<0;
		return 0;
	}
	n--;
	for(int i=2;i<=n;++i)
	{
		if(!zhi[i])
		{
			phi[i]=i-1;
			zhi[i]=i;
			shu[++sum]=i;
		}
		for(int j=1;j<=sum&&shu[j]*i<=n;++j)
		{
			if(shu[j]==zhi[i])
			{
				phi[i*shu[j]]=shu[j]*phi[i];
				zhi[i*shu[j]]=shu[j];
				break;
			}
			zhi[i*shu[j]]=shu[j];
			phi[i*shu[j]]=phi[i]*phi[shu[j]];
		}
	}
	for(int i=2;i<=n;++i)
		ans+=phi[i];
	ans*=2;
	ans+=3;
	cout<<ans;
	return 0;
}
