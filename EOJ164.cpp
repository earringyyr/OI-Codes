#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
long long n,m,k,sum,w,head[5010],d[5010],vis[5010],fa[5010],go[5010],num,t[250015];
struct node
{
	long long v;
	long long t;
	long long next;
}a[250015];
struct pi
{
	long long id;
	long long d;
	friend bool operator < (pi aa,pi bb)
	{
		return aa.d>bb.d;
	}
};
priority_queue<pi> q;
void ins(long long u,long long v,long long t)
{
	++sum;
	a[sum].v=v;
	a[sum].t=t;
	a[sum].next=head[u];
	head[u]=sum;
	return;
} 
void dij()
{
	for(long long i=1;i<=n;++i)
		d[i]=0x3f3f3f;
	pi lin;
	lin.id=n;
	lin.d=0;
	q.push(lin);
	d[n]=0;
	while(!q.empty())
	{
		pi lin=q.top();
		q.pop();
		long long id=lin.id;
		if(vis[id])
			continue;
		vis[id]=1;
		if(id==1)
			break;
		long long dd=head[id];
		while(dd)
		{
			if(!vis[a[dd].v])
			{
				if(d[id]+a[dd].t<d[a[dd].v])
				{
					d[a[dd].v]=d[id]+a[dd].t;
					fa[a[dd].v]=id; 
					go[a[dd].v]=a[dd].t;
					pi lin;
					lin.id=a[dd].v;
					lin.d=d[a[dd].v];
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
	cin>>n>>m>>k;
	for(long long i=1;i<=m;++i)
	{
		long long u,v,t;
		cin>>u>>v>>t;
		ins(u,v,t);
		ins(v,u,t);
	}
	cin>>w;
	dij();
	long long dd=1;
	while(dd!=n)
	{
		t[++num]=go[dd];
		dd=fa[dd];
	}
	sort(t+1,t+num+1);
	for(long long i=num;i>=1&&num-i+1<=k;--i)
		t[i]/=2;
	for(long long i=1;i<=num;++i)
		t[0]+=t[i];
	if(t[0]<=w)
		cout<<"YES"<<endl;
	else
		cout<<"QaQ"<<endl;
	cout<<t[0]%10000009;
	return 0;
}
