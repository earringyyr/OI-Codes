#include<iostream>
#include<cstdio>
using namespace std;
int f[101][101],a[101];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	f[0][0]=1;
	for(int i=1;i<=n;++i)
		for(int k=0;k<=a[i];++k)
			for(int j=k;j<=m;++j)
				f[i][j]=(f[i][j]+f[i-1][j-k])%1000007;
	cout<<f[n][m];
	return 0;
} 
