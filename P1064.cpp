#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m,v[61]={0},p[61]={0},q[61]={0},wu[61][61]={0},sum[61]={0},f[32001]={0};
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>v[i]>>p[i]>>q[i];
		if(q[i]>0)
		{
			wu[q[i]][++sum[q[i]]]=i;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(q[i]==0)
		{
			for(int x=n;x>=1;x--)
			{
				for(int j=1;j<=sum[i];j++)
				{
					for(int k=j+1;k<=sum[i];k++)
					{
						if(x-v[i]-v[wu[i][j]]-v[wu[i][k]]>=0)
							f[x]=max(f[x],f[x-v[i]-v[wu[i][j]]-v[wu[i][k]]]+v[i]*p[i]+v[wu[i][j]]*p[wu[i][j]]+v[wu[i][k]]*p[wu[i][k]]);
					}
				}
				for(int j=1;j<=sum[i];j++)
				{
					if(x-v[i]-v[wu[i][j]]>=0)
						f[x]=max(f[x],f[x-v[i]-v[wu[i][j]]]+v[i]*p[i]+v[wu[i][j]]*p[wu[i][j]]);
				}
				if(x-v[i]>=0)
					f[x]=max(f[x],f[x-v[i]]+v[i]*p[i]);
			}
		}
	}
	cout<<f[n];
	return 0;
}
