#include<iostream>
#include<cstdio>
using namespace std;
#define lch id*2
#define rch id*2+1
int n,m,sum,cnt,root;
int b[100005],head[100005];
int dep[100005],siz[100005];
int son[100005],top[100005];
int dfn[100005],num[100005];
int fa[100005];
struct node
{
	int v;
	int next;
}a[200005];
struct tree
{
	int l;
	int r;
	int num;
	int lazy;
}tr[400005];
void ins(int u,int v)
{
	++sum;
	a[sum].v=v;
	a[sum].next=head[u];
	head[u]=sum;
	return;
} 
void dfs1(int id,int f,int deep)
{
	fa[id]=f;
	dep[id]=deep;
	son[id]=-1;
	int d=head[id];
	while(d)
	{
		if(a[d].v!=f)
		{
			dfs1(a[d].v,id,deep+1);
			if(son[id]==-1||siz[a[d].v]>siz[son[id]])
				son[id]=a[d].v;
		}
		d=a[d].next;
	}
	return;
}
void dfs2(int id,int topf)
{
	++cnt;
	dfn[id]=cnt;
	num[cnt]=id;
	top[id]=topf;
	if(son[id]!=-1)
		dfs2(son[id],topf);
	int d=head[id];
	while(d)
	{
		if(a[d].v!=fa[id]&&a[d].v!=son[id])
			dfs2(a[d].v,a[d].v);
		d=a[d].next;
	}
	return;
} 
void pushdown(int id)
{
	if(tr[id].l!=tr[id].r)
	{
		int lazy=tr[id].lazy;
		tr[id].lazy=0;
		tr[lch].lazy=lazy;
		tr[rch].lazy=lazy;
		tr[lch].num=lazy;
		tr[rch].num=lazy;
	}
	return;
} 
void build(int id,int l,int r)
{
	tr[id].l=l;
	tr[id].r=r;
	if(l==r)
	{
		tr[id].num=num[l];
		return;
	}
	int mid=(l+r)/2;
	build(lch,l,mid);
	build(rch,mid+1,r);
	tr[id].num=min(tr[lch].num,tr[rch].num);
}
void add(int id,int l,int r,int val)
{
	pushdown(id);
	if(tr[id].l==l&&tr[id].r==r)
	{
		tr[id].lazy=val;
		tr[id].num=val;
		return;
	}
	int mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		add(lch,l,mid,val);
	if(l>=mid+1)
		add(rch,mid+1,r,val);
	if(l<=mid&&r>=mid+1)
	{
		add(lch,l,mid,val);
		add(rch,mid+1,r,val);
	}
	tr[id].num=min(tr[lch].num,tr[rch].num);
	return;
}
int ask(int id,int l,int r)
{
	pushdown(id);
	if(tr[id].l==l&&tr[id].r==r)
		return tr[id].num;
	int mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		return ask(lch,l,r);
	if(l>=mid+1)
		return ask(rch,l,r);
	if(l<=mid&&r>=mid+1)
		return min(ask(lch,l,mid),ask(rch,mid+1,r));
}
void lian_add(int x,int y,int val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		add(1,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	add(1,dfn[x],dfn[y],val);
	return;
}
int shu_ask(int id)
{
	if(id==root)
		return ask(1,1,n);
	else
		if(dfn[id]>=dfn[root]&&dfn[id]+siz[id]-1<=dfn[root])
		{
			int d=head[id];
			while(d)
			{
				if(dfn[a[d].v]>=dfn[root]&&dfn[a[d].v]+siz[a[d].v]-1<=dfn[root])
					break;
				d=a[d].next;
			}
			return ask(1,1,n)-ask(1,dfn[a[d].v],dfn[a[d].v]+siz[a[d].v]-1);
		}
		else
			return ask(1,dfn[id],dfn[id]+siz[id]-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ins(u,v);
		ins(v,u);
	}
	for(int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	scanf("%d",&root);
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
			scanf("%d",&root);
		if(opt==2)
		{
			int p1,p2,v;
			scanf("%d%d%d",&p1,&p2,&v);
			lian_add(p1,p2,v);
		}
		if(opt==3)
		{
			int id;
			scanf("%d",&id);
			printf("%d\n",shu_ask(id));
		}
	}
	return 0;
}
