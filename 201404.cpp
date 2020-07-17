#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int fen,n,m,r,c,a[20][20],min=100000000;
	cin>>n>>m>>r>>c;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n-r+1;i++)
		for(int j=1;j<=m-c+1;j++)
		{
			fen=0;
			for(int x=i;x<=i+r-1;x++)
				for(int y=j;y<j+c-1;y++)
					fen+=abs(a[x][y]-a[x][y+1]);
			for(int x=i;x<i+r-1;x++)
				for(int y=j;y<=j+c-1;y++)
					fen+=abs(a[x][y]-a[x+1][y]);
			if(fen<min)
				min=fen;
		}
	cout<<min;
	return 0;
}
