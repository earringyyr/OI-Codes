#include<iostream>
#include<cstdio>
using namespace std;
char b[20][20];	
int a[20][20],shu=0,zoux[5]={0,1,-1,1,-1},zouy[5]={0,-1,1,1,-1};
void guangsou(int m,int n)
{
	int tou=0,x,y,wei=1,z[10000][2];
	shu++;
	z[1][1]=n;
	z[1][2]=m;
	a[m][n]=0;
	do
	{
		tou++;
		for(int i=1;i<=4;i++)
		{
			x=z[tou][1]+zoux[i];
			y=z[tou][2]+zouy[i];
			if(a[x][y]!=0&&x>=1&&x<=n&&y>=1&&y<=m)
			{
				wei++;
				z[wei][1]=x+zouy[i];
				z[wei][2]=y+zoux[i];
				a[x][y]=0;
			}
		}
	}
	while(tou<wei);
}
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>b[i][j];
			a[i][j]=int(b[i][j])-48;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]!=0)
				guangsou(i,j);
	cout<<shu;
	return 0;
}
