#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int go[1001][1001];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int i,j,n;
	cin>>n>>i>>j;
	memset(go,1,sizeof(go));
	for(int x=1;x<=n;x++)
		for(int y=1;y<=n;y++)
			go[x][y]=0;
	go[1][1]=1;
	int x=1,y=1,sum=1,dox[5]={0,1,0,-1,0},doy[5]={0,0,1,0,-1},don=1;
	do
	{
		while(go[y+doy[don]][x+dox[don]]==0)
		{
			x=x+dox[don];
			y=y+doy[don];
			go[y][x]=++sum;
		}
		don++;
		if(don==5)
			don=1;
	}
	while(x!=ceil(n*1.0/2)||y!=n/2+1);
	cout<<go[i][j];
	return 0;
} 
