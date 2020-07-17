#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[2501][2501],f[2501][2501],m[3][2501][2501];
int main()
{
	int n,mm;
	while(cin>>n>>mm)
	{
		int ans=0;
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		memset(m,0,sizeof(m));
		for(register int i=1;i<=n;++i)
		{
			for(register int j=1;j<=mm;++j)
			{
				cin>>a[i][j];
				if(a[i][j]==1)
				{
					f[i][j]=1;
					m[1][i][j]=0;
					m[2][i][j]=0;
				}
				else
				{
					m[1][i][j]=m[1][i][j-1]+1;
					m[2][i][j]=m[2][i-1][j]+1;
				}
			}
		}
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=mm;++j)
				if(a[i][j]==1)
				{
					if(f[i-1][j-1]>=1)
						f[i][j]=max(f[i][j],min(f[i-1][j-1],min(m[1][i][j-1],m[2][i-1][j]))+1);
					if(f[i][j]>ans)
						ans=f[i][j];
				}
		for(register int i=1;i<=n;++i)
			for(register int j=mm;j>=1;j--)
				if(a[i][j]==0)
					m[1][i][j]=m[1][i][j+1]+1;
				else
					m[1][i][j]=0;
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=mm;++j)
				if(a[i][j]==1)
				{
					if(f[i-1][j+1]>=1)
						f[i][j]=max(f[i][j],min(f[i-1][j+1],min(m[1][i][j+1],m[2][i-1][j]))+1);
					if(f[i][j]>ans)
						ans=f[i][j];
				}
		cout<<ans<<endl;
	} 
	return 0;
} 
