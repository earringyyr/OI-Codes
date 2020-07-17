#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char map[1001][1001];
int t=0,n,m,sum[100001],go[1001][1001],tu[1001][1001],l[1000001][3],gox[5]={0,1,-1,0,0},goy[5]={0,0,0,1,-1};
int bfs(int x,int y)
{
	//memset(l,0,sizeof(l));
	int head=0,tail=1;
	if(go[x][y]!=0)
	{
		return sum[go[x][y]];
	}
	t++;
	l[1][1]=x;
	l[1][2]=y;
	go[x][y]=t;
	do
	{
		head++;
		for(int i=1;i<=4;i++)
		{
			x=l[head][1]+gox[i];
			y=l[head][2]+goy[i];
			if(go[x][y]==0&&tu[x][y]!=tu[l[head][1]][l[head][2]]&&x>=1&&y>=1&&x<=n&&y<=n)
			{
				tail++;
				go[x][y]=t;
				l[tail][1]=x;
				l[tail][2]=y;
			}
		}
	}while(head<tail);
	sum[t]=tail;
	return tail;
	
}
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>map[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			tu[i][j]=int(map[i][j]-'0');
	for(int i=1;i<=m;i++)
	{
		int x,y,num;
	//	cin>>x>>y;
		scanf("%d%d",&x,&y);
		num=bfs(x,y);
		cout<<num<<endl;
	} 
	return 0;
}
