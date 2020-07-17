#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
long long f[1001][1001]={0};
int main()
{
	//freopen("bea.in","r",stdin);
	//freopen("bea.out","w",stdout);
	for(int i=0;i<=1000;i++)
	{
		f[i][i]=1;
	}
	for(int i=1;i<=1000;i++)
	{
		for(int j=i+1;j<=1000;j++)
		{
			f[i][j]+=f[i][j-1];
			if(j-i>=2)
				f[i][j]+=f[i][j-2];
		}
	}
	cin>>n;
	for(int x=1;x<=n;x++)
	{
		int a,b;
		cin>>a>>b;
		cout<<f[a][b]<<endl;
	} 
	return 0;
} 
