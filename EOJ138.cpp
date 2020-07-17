#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int n,m,sum,vis[5005][3];
int h[5005],w[5005],s[5005],head[5005];
int ans=0x3f3f3f,d[5005][2];
struct node
{
	int v;
	int w;
	int next;
}a[30005];
struct pi
{
	int d;
	int num;
	int tai;
	friend bool operator < (pi aaa,pi bbb)
	{
		return aaa.d>bbb.d;
	}
};
priority_queue<pi> q;
void ins(int u,int v,int w)
{
	++sum;
	a[sum].v=v;
	a[sum].w=w;
	a[sum].next=head[u];
	head[u]=sum;
	return;
}
void dij()
{
	pi lin;
	lin.num=1;
	lin.d=0;
	lin.tai=1;
	q.push(lin);
	d[1][1]=0;
	while(!q.empty())
	{
		pi k=q.top();
		q.pop();
		int num=k.num,tai=k.tai;
		if(vis[num][tai%2]==1)
			continue;
		vis[num][tai%2]=1;
		int nu=0;
		if(tai%2==1&&h[num]==1)
			if(d[num][0]>d[num][1]+s[num])
			{
				d[num][0]=d[num][1]+s[num];
				pi lin;
				lin.num=num;
				lin.d=d[num][0];
				lin.tai=0;
				q.push(lin);
			}
		if(tai%2==0&&h[num]==0)
			if(d[num][1]>d[num][0]+s[num])
			{
				d[num][1]=d[num][0]+s[num];
				pi lin;
				lin.num=num;
				lin.d=d[num][1];
				lin.tai=1;
				q.push(lin);
			}
		if(tai%2==1&&h[num]==0)
			if(d[num][0]>d[num][1])
			{
				d[num][0]=d[num][1];
				pi lin;
				lin.num=num;
				lin.d=d[num][0];
				lin.tai=0;
				q.push(lin);
			}
		if(tai%2==0&&h[num]==1)
			if(d[num][1]>d[num][0])
			{
				d[num][1]=d[num][0];
				pi lin;
				lin.num=num;
				lin.d=d[num][1];
				lin.tai=1;
				q.push(lin);
			}
		int dd=head[num];
		while(dd)
		{
			if(tai%2==1)
			{
				int lin=a[dd].w;
				if(h[num]!=h[a[dd].v])
				{
					if(h[num]==0&&h[a[dd].v]==1)
					{
						lin-=abs(w[num]-w[a[dd].v]);
						if(lin<0)
							lin=0;
					}
					if(h[num]==1&&h[a[dd].v]==0)
						lin+=abs(w[num]-w[a[dd].v]);
				}
				if(lin+d[num][1]<d[a[dd].v][0])
				{
					d[a[dd].v][0]=lin+d[num][1];
					pi lin;
					lin.d=d[a[dd].v][0];
					lin.tai=0;
					lin.num=a[dd].v;
					q.push(lin);
				}
			}
			else
			{
				int lin=a[dd].w;
				if(h[num]!=h[a[dd].v])
				{
					if(h[num]==1&&h[a[dd].v]==0)
					{
						lin-=abs(w[num]-w[a[dd].v]);
						if(lin<0)
							lin=0;
					}
					if(h[num]==0&&h[a[dd].v]==1)
						lin+=abs(w[num]-w[a[dd].v]);
				}
				if(lin+d[num][0]<d[a[dd].v][1])
				{
					d[a[dd].v][1]=lin+d[num][0];
					pi lin;
					lin.d=d[a[dd].v][1];
					lin.tai=1;
					lin.num=a[dd].v;
					q.push(lin);
				}
			}
			dd=a[dd].next;
		}
	}
	return;
}
int main()
{
	for(int i=0;i<5005;++i)
		d[i][0]=d[i][1]=0x3f3f3f;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>h[i];
	for(int i=1;i<=n;++i)
		cin>>w[i];
	for(int i=1;i<=n;++i)
		cin>>s[i];
	for(int i=1;i<=m;++i)
	{
		int u,v,k;
		cin>>u>>v>>k;
		ins(u,v,k);
	}
	dij();
	cout<<min(d[n][1],d[n][0]);
	return 0;
}
