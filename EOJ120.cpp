#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define lch id*2
#define rch id*2+1
int n,m;
struct node
{
	int l;
	int r;
	int num;
	int lazy;
}tr[40000005];
void build(int id,int l,int r)
{
	tr[id].l=l;
	tr[id].r=r;
	tr[id].num=0;
	tr[id].lazy=0;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(lch,l,mid);
	build(rch,mid+1,r);
	return;
}
void pushdown(int id)
{
	if(tr[id].l!=tr[id].r&&tr[id].lazy!=0)
	{
		tr[id].lazy=0;
		tr[lch].num=1;
		tr[rch].num=1;
		tr[lch].lazy=1;
		tr[rch].lazy=1;
	}
	return;
}
void add(int id,int l,int r)
{
	pushdown(id);
	if(tr[id].l==l&&tr[id].r==r)
	{
		tr[id].lazy=1;
		tr[id].num=1;
		return;
	}
	int mid=(tr[id].l+tr[id].r)>>1;
	if(r<=mid)
		add(lch,l,r);
	if(l>=mid+1)
		add(rch,l,r);
	if(l<=mid&&r>=mid+1)
	{
		add(lch,l,mid);
		add(rch,mid+1,r);
	}
	tr[id].num=min(tr[lch].num,tr[rch].num);
	return;
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int tt=1;tt<=t;++tt)
	{
		scanf("%d%d",&n,&m);
		build(1,1,m);
		for(int i=1;i<=n;++i)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			add(1,a,b);
		}
		if(tr[1].num>0)
			printf("1\n");
		else
			printf("0\n");
	}
	return 0;
}
