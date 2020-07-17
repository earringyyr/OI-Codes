#include<iostream>
#include<cstdio>
using namespace std;
int r,a[1001][1001],f[1001][1001];
int main()
{
	cin>>r;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	f[1][1]=a[1][1];
	for(int i=2;i<=r;i++)
		for(int j=1;j<=i;j++)
		{
			if(j!=1)
				f[i][j]=max(f[i][j],f[i-1][j-1]+a[i][j]);
			if(j!=i)
				f[i][j]=max(f[i][j],f[i-1][j]+a[i][j]);
		}
	int ma=0;
	for(int i=1;i<=r;i++)
		ma=max(ma,f[r][i]);
	cout<<ma;
	return 0;
}
