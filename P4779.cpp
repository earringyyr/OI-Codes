#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
#define inf 1000000000
long long n,m,s,sum,head[100005],d[100005],use[100005];
struct node
{
    long long v;
    long long w;
    long long next;
}a[200005];
struct pi
{
    long long hao;
    long long d;
    friend bool operator < (pi aa,pi bb)
    {
        return aa.d>bb.d;
    }
};
void ins(long long u,long long v,long long w)
{
    ++sum;
    a[sum].v=v;
    a[sum].w=w;
    a[sum].next=head[u];
    head[u]=sum;
    return;
}
int main()
{
    for(long long i=0;i<100005;++i)
        d[i]=inf;
    priority_queue<pi> q;
    cin>>n>>m>>s;
    for(long long i=1;i<=m;++i)
    {
        long long u,v,w;
        cin>>u>>v>>w;
        ins(u,v,w);
    }
    pi lin;
    lin.hao=s;
    lin.d=0;
    q.push(lin);
    d[s]=0;
    while(!q.empty())
    {
        pi k=q.top();
        q.pop();
        if(use[k.hao]==1)
            continue;
        use[k.hao]=1;
        long long kk=head[k.hao];
        while(kk)
        {
            if(!use[a[kk].v])
                if(d[k.hao]+a[kk].w<d[a[kk].v])
                {
                    d[a[kk].v]=d[k.hao]+a[kk].w;
                    pi lin;
                    lin.hao=a[kk].v;
                    lin.d=d[a[kk].v];
                    q.push(lin);
                }
            kk=a[kk].next;
        }
    }
    for(long long i=1;i<=n;++i)
        cout<<d[i]<<" ";
    return 0;
}
