#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[51][51][51][51];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int m,n,cla[51][51];
	cin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>cla[i][j]; 
	for(int a=1;a<=m;a++)
		for(int b=1;b<=n;b++)
			for(int c=1;c<=m;c++)
				for(int d=1;d<=n;d++)
				{
					if(a==c&&b==d&&a!=m&&b!=n)
						continue;
					int ma=0;
					ma=max(ma,f[a-1][b][c-1][d]);
					ma=max(ma,f[a-1][b][c][d-1]);
					ma=max(ma,f[a][b-1][c-1][d]);
					ma=max(ma,f[a][b-1][c][d-1]);
					f[a][b][c][d]=ma+cla[a][b]+cla[c][d];
				}
	cout<<f[m][n-1][m-1][n];
	return 0;
}
