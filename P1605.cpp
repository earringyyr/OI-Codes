#include<iostream>
#include<cstdio>
using namespace std;
int map[6][6],num=0,gox[5]={0,1,-1,0,0},goy[5]={0,0,0,1,-1},n,m,t,sx,sy,fx,fy,a,b;
int search(int x,int y)
{
	if(x<0||y<0||x>m||y>n)
		return 0;
	if(x==fx&&y==fy)
	{
		num++;
		return 0;
	}
	int p,q;
	for(int i=1;i<=4;i++)
	{
		p=x+gox[i];
		q=y+goy[i];
		if(map[p][q]==0&&x>=1&&x<=m&&y>=1&&y<=n)
		{
			map[p][q]=1;
			search(p,q);
			map[p][q]=0;
		}
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>m>>t;
	cin>>sx>>sy>>fx>>fy;
	for(int i=1;i<=t;i++)
	{
		cin>>a>>b;
		map[a][b]=1;
	}
	map[sx][sy]=1;
	search(sx,sy);
	cout<<num;
	return 0;
}
