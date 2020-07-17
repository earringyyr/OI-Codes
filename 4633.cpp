#include<iostream>
#include<cstdio>
using namespace std;
#define lch id*2
#define rch id*2+1
long long n,m,sum,r,p,cnt,b[100005],head[100005],siz[100005],top[100005],son[100005],dep[100005],fa[100005],dfn[100005],num[100005];
struct node
{
	long long v;
	long long next;
}a[200005];
struct tree
{
	long long l;
	long long r;
	long long num;
	long long lazy;
}tr[400005];
void ins(long long u,long long v)
{
	++sum;
	a[sum].v=v;
	a[sum].next=head[u];
	head[u]=sum;
	return;
}
void dfs1(long long id,long long f,long long deep)
{
	fa[id]=f;
	dep[id]=deep;
	siz[id]=1;
	son[id]=-1;
	long long d=head[id];
	while(d)
	{
		if(a[d].v!=f)
		{
			dfs1(a[d].v,id,deep+1);
			siz[id]+=siz[a[d].v];
			if(siz[id]==-1||siz[son[id]]<siz[a[d].v])
				son[id]=a[d].v;
		}
		d=a[d].next;
	}
	return;
}
void dfs2(long long id,long long topf)
{
	top[id]=topf;
	dfn[id]=++cnt;
	num[cnt]=b[id];
	if(son[id]!=-1)
		dfs2(son[id],topf);
	long long d=head[id];
	while(d)
	{
		if(a[d].v!=fa[id]&&a[d].v!=son[id])
			dfs2(a[d].v,a[d].v);
		d=a[d].next;
	}
	return;
}
void build(long long id,long long l,long long r)
{
	tr[id].l=l;
	tr[id].r=r;
	if(l==r)
	{
		tr[id].num=num[l];
		return;
	}
	long long mid=(l+r)/2;
	build(lch,l,mid);
	build(rch,mid+1,r);
	tr[id].num=(tr[lch].num+tr[rch].num)%p;
	return;
}
void pushdown(long long id)
{
	if(tr[id].l!=tr[id].r)
	{
		long long lazy=tr[id].lazy;
		tr[id].lazy=0;
		tr[lch].lazy+=lazy;
		tr[rch].lazy+=lazy;
		tr[lch].num+=lazy*(tr[lch].r-tr[lch].l+1);
		tr[rch].num+=lazy*(tr[rch].r-tr[rch].l+1);
		tr[lch].num%=p;
		tr[rch].num%=p;
		tr[lch].lazy%=p;
		tr[rch].lazy%=p;
	}
	return;
}
void add(long long id,long long l,long long r,long long val)
{
	pushdown(id);
	if(tr[id].l==l&&tr[id].r==r)
	{
		tr[id].lazy+=val;
		tr[id].num+=val*(tr[id].r-tr[id].l+1);
		tr[id].lazy%=p;
		tr[id].num%=p;
		return;
	}
	long long mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		add(lch,l,r,val);
	if(l>=mid+1)
		add(rch,l,r,val);
	if(l<=mid&&r>=mid+1)
	{
		add(lch,l,mid,val);
		add(rch,mid+1,r,val);
	}
	tr[id].num=(tr[lch].num+tr[rch].num)%p;
	return;
}
long long ask(long long id,long long l,long long r)
{
	pushdown(id);
	if(tr[id].l==l&&tr[id].r==r)
		return tr[id].num;
	long long mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		return ask(lch,l,r);
	if(l>=mid+1)
		return ask(rch,l,r);
	if(l<=mid&&r>=mid+1)
		return (ask(lch,l,mid)+ask(rch,mid+1,r))%p;
}
void lian(long long x,long long y,long long val)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		add(1,dfn[top[x]],dfn[x],val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	add(1,dfn[x],dfn[y],val);
	return;
}
long long ask_lian(long long x,long long y)
{
	long long ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans+=ask(1,dfn[top[x]],dfn[x]);
		ans%=p;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ans+=ask(1,dfn[x],dfn[y]);
	ans%=p;
	return ans;
}
int main()
{
	r=1;
	p=1000000000;
	scanf("%lld",&n);
	for(long long i=1;i<n;++i)
	{
		long long x,y;
		scanf("%lld%lld",&x,&y);
		ins(x,y);
		ins(y,x);
	}
	dfs1(r,0,1);
	dfs2(r,r);
	build(1,1,n);
	scanf("%lld",&m);
	for(long long i=1;i<=m;++i)
	{
		long long pan;
		scanf("%lld",&pan);
		if(pan==1)
		{
			long long x,y;
			scanf("%lld%lld",&x,&y);
			lian(x,y,1);
		}
		if(pan==2)
		{
			long long x,y;
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",ask_lian(x,y));
		}
	}
	return 0;
}
