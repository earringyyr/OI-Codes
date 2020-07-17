#include<iostream>
#include<cstdio>
#define lch id*2
#define rch id*2+1
using namespace std;
long long a[100001];
long long n,m;
struct node
{
    long long l;
    long long r;
    long long sum;
    long long lazy;
}c[100001<<4];
void build(long long id,long long l,long long r)
{
    c[id].l=l;
    c[id].r=r;
    if(l==r)
    {
        c[id].sum=a[l];
        return;	
    }
    long long mid=(l+r)/2;
    build(lch,l,mid);
    build(rch,mid+1,r);
    c[id].sum=c[lch].sum+c[rch].sum;
    return;
}
void pushdown(long long id)
{
    if(c[id].lazy&&c[id].l!=c[id].r)
    {
        long long lazy=c[id].lazy;
        c[id].lazy=0;
        c[lch].lazy+=lazy;
        c[rch].lazy+=lazy;
        c[lch].sum+=(c[lch].r-c[lch].l+1)*lazy;	
        c[rch].sum+=(c[rch].r-c[rch].l+1)*lazy;
    }
    return;
}
void add(long long id,long long l,long long r,long long val)
{
    pushdown(id);
    if(c[id].l==l&&c[id].r==r)	
    {
        c[id].lazy+=val;
        c[id].sum+=(r-l+1)*val	;
        return;
    }
    long long mid=(c[id].l+c[id].r)/2;
    if(mid<l)
    {
        add(rch,l,r,val);
 	    c[id].sum=c[lch].sum+c[rch].sum; 
        return;
    }
    if(mid+1>r)
    {
        add(lch,l,r,val);	
  	    c[id].sum=c[lch].sum+c[rch].sum; 
        return;
    }
    add(lch,l,mid,val);
    add(rch,mid+1,r,val);
    c[id].sum=c[lch].sum+c[rch].sum; 
    return;
}
long long ask(long long id,long long l,long long r)
{
    pushdown(id);
    if(c[id].l==l&&c[id].r==r)
        return c[id].sum;
    long long mid=(c[id].l+c[id].r)/2;
    if(mid<l)
        return ask(rch,l,r);
    if(mid+1>r)
        return ask(lch,l,r);
    return ask(lch,l,mid)+ask(rch,mid+1,r);
}
int main()
{
    cin>>n>>m;
    for(long long i=1;i<=n;++i)
        cin>>a[i];
    build(1,1,n);
    for(long long i=1;i<=m;++i)
    {
        long long pan,x,y,k;
        cin>>pan;
        if(pan==1)
        {
            cin>>x>>y>>k;
            add(1,x,y,k);
        }
        else
        {
            cin>>x>>y;
            cout<<ask(1,x,y)<<endl;
        }
    }
    return 0;
}	
