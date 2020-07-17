#include<iostream>
#include<cstdio>
using namespace std;
#define lch id*2
#define rch id*2+1
struct node
{
	int num;
	int l;
	int r;
}tr[2000005];
void build(int id,int l,int r)
{
	tr[id].l=l;
	tr[id].r=r;
	if(l==r)
	{
		tr[id].num=1;
		return;
	}
	int mid=(l+r)/2;
	build(lch,l,mid);
	build(rch,mid+1,r);
	tr[id].num=tr[lch].num+tr[rch].num;
	return;
}
void change(int id,int l,int r)
{
	if(tr[id].num==0)
		return;
	if(tr[id].l==l&&tr[id].r==r)
	{
		tr[id].num=0;
		return;
	}
	int mid=(tr[id].l+tr[id].r)/2;
	if(r<=mid)
		change(lch,l,r);
	if(l>=mid+1)
		change(rch,l,r);
	if(l<=mid&&r>=mid+1)
	{
		change(lch,l,mid);
		change(rch,mid+1,r);
	}
	tr[id].num=tr[lch].num+tr[rch].num;
	return;
}
int main()
{
	int n,m;
	cin>>n>>m;
	build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		change(1,l,r);
		printf("%d\n",tr[1].num);
	} 
	return 0;
}
