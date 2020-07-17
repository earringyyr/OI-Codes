#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int pai[101][101][101];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	bool can=false;
	int c[101],a[101][101]={0},p,go[101][101]={0},d,n,k,m,s,t,u,v;
	memset(go,9999,sizeof(go));
	cin>>n>>k>>m>>s>>t;
	for(int i=1;i<=n;i++)
		cin>>c[i];
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			cin>>a[i][j];
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>d;
		go[u][v]=d;
		go[v][u]=d;
	}
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
		{
			for(int x=1;x<=k;x++)
			{
				pai[i][j][x]=pai[i][j][x];
			}
			for(int x=1;x<=k;x++)
			{
				pai[i][j][x]=a[j][x];
			}	
		}
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
			for(int l=i;l<=j;l++)
			{
				if(go[i][l]!=0&&go[l][j]!=0)
				{
					p=1;
					for(int x=1;x<=k;x++)
						if(pai[i][j][x]!=c[i]&&pai[i][j][x]!=c[l]&&pai[i][j][x]!=c[j])
						{
							if(go[i][l]+go[l][j]>go[i][j])
								go[i][j]=go[i][l]+go[l][j];	
						}
				}
			}
	cout<<go[s][t];	
	return 0;
}
