#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[201][201],a[201][201];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int m,n,table[201][201]={0},sx,sy;
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>table[i][j];
	sy=m+1;
	sx=n/2+1;
	a[sy][sx]=1;
	for(int i=m;i>=1;i--)
	{
		for(int l=1;l<=n;l++)
		{
			if(a[i+1][l]==1)
			{
				f[i][l]=max(f[i][l],f[i+1][l]+table[i][l]);
				a[i][l]=1;
				a[i][l+1]=1;
				a[i][l-1]=1;
			}
			if(a[i+1][l+1]==1)
			{
				f[i][l]=max(f[i][l],f[i+1][l+1]+table[i][l]);
				a[i][l]=1;
				a[i][l+1]=1;
				a[i][l+2]=1;
			}
			if(a[i+1][l-1]==1)
			{
				f[i][l]=max(f[i][l],f[i+1][l-1]+table[i][l]);
				a[i][l]=1;
				a[i][l-2]=1;
				a[i][l-1]=1;
			}
		}
	}
	int ma=-1000000000;
	for(int i=1;i<=n;i++)
	{
		ma=max(ma,f[1][i]);
	}
	cout<<ma;
	return 0;
}
