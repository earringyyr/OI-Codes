#include<iostream>
#include<cstdio>
using namespace std;
struct node
{
    int u;
    int v;
    int next;
}a[1000005];
int head[500005],sum=0,f[500005][100],deep[500005],lg[500005];
void ins(int u,int v)
{
    ++sum;
    a[sum].u=u;
    a[sum].v=v;
    a[sum].next=head[u];
    head[u]=sum;
    return;
}
void dfs(int k,int fa)
{
    deep[k]=deep[fa]+1; 
    f[k][0]=fa;
    for(int i=1;(1<<i)<=deep[k];++i)
        f[k][i]=f[f[k][i-1]][i-1];
    int d=head[k];
    while(d)
    {
        if(a[d].v!=fa)
            dfs(a[d].v,k);
        d=a[d].next;
    } 
    return;
}
int lca(int x,int y)
{
	while(deep[x]<deep[y])
		y=f[y][lg[deep[y]-deep[x]]-1];
	while(deep[y]<deep[x])
		x=f[x][lg[deep[x]-deep[y]]-1];
    if(x==y)
        return x;
    for(int i=lg[deep[x]]-1;i>=0;--i)
        if(f[x][i]!=f[y][i])
        {
            x=f[x][i];
            y=f[y][i];
        }
    return f[x][0];
}
int main()
{
    int n,m,s;
    cin>>n>>m>>s;
    for(int i=1;i<n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        ins(x,y);
        ins(y,x);
    } 
    dfs(s,0);
    for(int i=1;i<=n;++i)
    {
    	lg[i]=lg[i-1];
    	if(1<<lg[i-1]==i)
    		lg[i]++;
    }
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
} 
