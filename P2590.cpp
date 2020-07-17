#include<iostream>
#include<cstdio>
using namespace std;
#define lch id*2
#define rch id*2+1
int n,sum,cnt,head[30005],w[30005],dep[30005],siz[30005],fa[30005],top[30005],son[30005],dfn[30005],num[30005];
struct node
{
	int v;
	int next;
}a[60005];
struct tree
{
	int l;
	int r;
	int num;
	int ma;
}tr[120005];
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
	dep[id]=deep;
	fa[id]=f;
	siz[id]=1;
	son[id]=-1;
	int d=head[id];
	while(d)
	{
		if(a[d].v!=f)
		{
			dfs1(a[d].v,id,deep+1);
			siz[id]+=siz[a[d].v];
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
	num[cnt]=w[id];
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
void build(int id,int l,int r)
{
	tr[id].l=l;
	tr[id].r=r;
	if(l==r)
	{
		tr[id].num=num[l];
		tr[id].ma=num[l];
		return;
	}
	int mid=(tr[id].l+tr[id].r)/2;
	build(lch,l,mid);
	build(rch,mid+1,r);
	tr[id].num=tr[lch].num+tr[rch].num;
	tr[id].ma=max(tr[lch].ma,tr[rch].ma); 
	return;
}
void add(int id,int wei,int val)
{
	if(tr[id].l==wei&&tr[id].r==wei)
	{
		tr[id].num=val;
		tr[id].ma=val;
		return;
	}
	int mid=(tr[id].l+tr[id].r)/2;
	if(wei<=mid)
		add(lch,wei,val);
	else
		add(rch,wei,val);
	tr[id].num=tr[lch].num+tr[rch].num;
	tr[id].ma=max(tr[lch].ma,tr[rch].ma);
	return;
}
int ask_ma(int id,int l,int r)
{
	if(tr[id].l==l&&tr[id].r==r)
		return tr[id].ma;
	int mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		return ask_ma(lch,l,r);
	if(l>=mid+1)
		return ask_ma(rch,l,r);
	return max(ask_ma(lch,l,mid),ask_ma(rch,mid+1,r));
}
int ask_val(int id,int l,int r)
{
	if(tr[id].l==l&&tr[id].r==r)
		return tr[id].num;
	int mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		return ask_val(lch,l,r);
	if(l>=mid+1)
		return ask_val(rch,l,r);
	return ask_val(lch,l,mid)+ask_val(rch,mid+1,r);
}
int lian_ma(int x,int y)
{
	int ans=-1000000000;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans=max(ans,ask_ma(1,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	ans=max(ans,ask_ma(1,dfn[x],dfn[y]));
	return ans;
}
int lian_val(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ans+=ask_val(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	ans+=ask_val(1,dfn[x],dfn[y]);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ins(u,v);
		ins(v,u);
	}
	for(int i=1;i<=n;++i)
		cin>>w[i];
	dfs1(1,0,1); 
	dfs2(1,1);
	build(1,1,n);
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		string pan;
		cin>>pan;
		int u,t;
		scanf("%d%d",&u,&t);
		if(pan=="CHANGE")
			add(1,dfn[u],t);
		if(pan=="QMAX")
			printf("%d\n",lian_ma(u,t));
		if(pan=="QSUM")
			printf("%d\n",lian_val(u,t));
	}
	return 0;
} 
