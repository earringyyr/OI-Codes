#include<iostream>
#include<cstdio>
using namespace std;
#define INF 2147483647
int n,m,s,use[500001],head[500001],dis[500001];
struct node
{
	int g;
	int w;
	int next;
}a[500001];
int main()
{
	fill(dis,dis+500001,INF);
	cin>>n>>m>>s;
	for(int i=1;i<=m;++i)
	{
		int f;
		cin>>f;
		cin>>a[i].g>>a[i].w;
		a[i].next=head[f];
		head[f]=i;
	}
	dis[s]=0;
	for(int i=1;i<=n;++i)
	{
		int ma=INF,k;
		for(int j=1;j<=n;++j)
			if(use[j]==0&&dis[j]<ma)
			{
				ma=dis[j];
				k=j;
			}
		use[k]=1;
		int wei=k;
		k=head[k];
		if(use[a[k].g]==0&&dis[wei]+a[k].w<dis[a[k].g])
			dis[a[k].g]=dis[wei]+a[k].w;
		do
		{
			k=a[k].next;
			if(use[a[k].g]==0&&dis[wei]+a[k].w<dis[a[k].g])
				dis[a[k].g]=dis[wei]+a[k].w;
		}
		while(a[k].next!=0);
	}
	for(int i=1;i<=n;++i)
		cout<<dis[i]<<" ";
	return 0;
}
