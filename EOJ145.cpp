#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
double f[5005][5005];
int main()
{
	cin>>m>>n;
	f[0][0]=1;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=min(i,n);++j)
			f[i][j]=f[i-1][j-1]*(n-j+1)/n+f[i-1][j]*j/n;
	printf("%.5f",f[m][n]);
	return 0;
}
