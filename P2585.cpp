#include<iostream>
#include<cstdio>
using namespace std;
int n,sum,fa[500005],f[500005][3],ff[500005][3];
struct node
{
	int l;
	int r;
}tr[500005];
void init(int fafa)
{
	++sum;
	int len=sum;
	fa[sum]=fafa;
	char x;
	x=getchar(); 
	int pan;
	pan=x-'0';
	if(pan==0)
		return;
	if(pan==1)
	{
		tr[len].l=sum+1;
		init(len);
	}
	if(pan==2)
	{
		tr[len].l=sum+1;
		init(len);
		tr[len].r=sum+1;
		init(len);
	}
	return;
}
void dfs(int id,int co)
{
	if(f[id][co]!=-1&&ff[id][co]!=-1)
		return;
	if(co==1)
	{
		f[id][co]=1;
		ff[id][co]=1;
	}
	else
	{
		f[id][co]=0;
		ff[id][co]=0;
	}
	if(tr[id].l==0&&tr[id].r==0)
		return;
	if(tr[id].l==0||tr[id].r==0)
	{
		if(tr[id].l!=0)
			if(co==1)
			{
				dfs(tr[id].l,2);
				f[id][co]+=f[tr[id].l][2];
				ff[id][co]+=ff[tr[id].l][2];
			}
			else
			{
				dfs(tr[id].l,2);
				dfs(tr[id].l,1);
				f[id][co]+=max(f[tr[id].l][2],f[tr[id].l][1]);
				ff[id][co]+=min(ff[tr[id].l][2],ff[tr[id].l][1]);
			}
		else
			if(co==1)
			{
				dfs(tr[id].r,2);
				f[id][co]+=f[tr[id].r][2];
				ff[id][co]+=ff[tr[id].r][2];
			}
			else
			{
				dfs(tr[id].r,2);
				dfs(tr[id].r,1);
				f[id][co]+=max(f[tr[id].r][2],f[tr[id].r][1]);
				ff[id][co]+=min(ff[tr[id].r][2],ff[tr[id].r][1]);
			}
		return;
	}
	if(co==1)
	{
		dfs(tr[id].l,2);
		dfs(tr[id].r,2);
		f[id][co]+=f[tr[id].l][2]+f[tr[id].r][2];
		ff[id][co]+=ff[tr[id].l][2]+ff[tr[id].r][2];
	}
	if(co==2)
	{
		dfs(tr[id].l,1);
		dfs(tr[id].r,2);
		dfs(tr[id].l,2);
		dfs(tr[id].r,1);
		f[id][co]+=max(f[tr[id].l][1]+f[tr[id].r][2],f[tr[id].l][2]+f[tr[id].r][1]);
		ff[id][co]+=min(ff[tr[id].l][1]+ff[tr[id].r][2],ff[tr[id].l][2]+ff[tr[id].r][1]);
	}
	return;
}
int main()
{
	for(int i=0;i<500005;++i)
		for(int j=0;j<3;++j)
		{
			f[i][j]=-1;
			ff[i][j]=-1;
		}
	init(0);
	n=sum;
	dfs(1,1);
	dfs(1,2);
	cout<<max(f[1][1],f[1][2])<<" ";
	cout<<min(ff[1][1],ff[1][2]);
	return 0;
}
