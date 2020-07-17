#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define inf 100000000
int sum,head[300000],d[300000],use[300000];
int r,c;
struct pi
{
	int hao;
	int num;
	friend bool operator < (pi aa,pi bb)
	{
		return aa.num>bb.num;
	}
};
priority_queue<pi> q;
struct node
{
	int v;
	int num;
	int next;
}a[2000000];
void ins1(int u,int v)
{
	++sum;
	a[sum].next=head[u];
	head[u]=sum;
	a[sum].num=1;
	a[sum].v=v;
	return;
}
void ins0(int u,int v)
{
	++sum;
	a[sum].next=head[u];
	head[u]=sum;
	a[sum].num=0;
	a[sum].v=v;
	return;
}
void dijstra()
{
	pi lin;
	lin.hao=1;
	lin.num=0;
	q.push(lin);
	d[1]=0;
	while(!q.empty())
	{
		pi k=q.top();
		q.pop();
		if(use[k.hao]==1)
			continue;
		use[k.hao]=1;
		if(k.hao==(c+1)*(r+1))
			break;
		int dd=head[k.hao];
		while(dd)
		{
			if(!use[a[dd].v])
			{
				if(d[k.hao]+a[dd].num<d[a[dd].v])
				{
					d[a[dd].v]=d[k.hao]+a[dd].num;
					pi lin;
					lin.num=d[a[dd].v];
					lin.hao=a[dd].v;
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
	int t;
	cin>>t;
	for(int tt=1;tt<=t;++tt)
	{
		while(!q.empty())
			q.pop();
		for(int i=0;i<300000;++i)
			d[i]=inf;
		memset(head,0,sizeof(head));
		memset(use,0,sizeof(use));
		sum=0;
		cin>>r>>c;
		for(int i=1;i<=r;++i)
			for(int j=1;j<=c;++j)
			{
				char rc;
				cin>>rc;
				if(rc=='/')
				{
					ins1((c+1)*(i-1)+j,(c+1)*i+j+1);
					ins0((c+1)*(i-1)+j+1,(c+1)*i+j);
					ins1((c+1)*i+j+1,(c+1)*(i-1)+j);
					ins0((c+1)*i+j,(c+1)*(i-1)+j+1);
				}
				else
				{
					ins0((c+1)*(i-1)+j,(c+1)*i+j+1);
					ins1((c+1)*(i-1)+j+1,(c+1)*i+j);
					ins0((c+1)*i+j+1,(c+1)*(i-1)+j);
					ins1((c+1)*i+j,(c+1)*(i-1)+j+1);
				}
			}
		dijstra();
		if(d[(c+1)*(r+1)]==inf)
			cout<<"NO SOLUTION"<<endl;
		else
			cout<<d[(c+1)*(r+1)]<<endl;
	}
	return 0;
}
