#include<iostream>
#include<cstdio>
#define lch id*2
#define rch id*2+1
using namespace std;
long long a[100001];
long long n,m,p;
struct node
{
    long long l;
    long long r;
    long long sum;
    long long lazy_jia;
    long long lazy_cheng;
    node()
    {
    	lazy_cheng=1;
    }
}c[100001<<4];
void build(long long id,long long l,long long r)
{
    c[id].l=l;
    c[id].r=r;
    if(l==r)
    {
        c[id].sum=a[l]%p;
        return;	
    }
    long long mid=(l+r)/2;
    build(lch,l,mid);
    build(rch,mid+1,r);
    c[id].sum=(c[lch].sum+c[rch].sum)%p;
    return;
}
void pushdown_cheng(long long id)
{
    if(c[id].lazy_cheng&&c[id].l!=c[id].r)
    {
        long long lazy=c[id].lazy_cheng;
        c[id].lazy_cheng=1;
        c[lch].lazy_cheng*=lazy;
        c[rch].lazy_cheng*=lazy;
        c[lch].sum*=lazy;	
        c[rch].sum*=lazy;
        c[lch].sum%=p;
        c[rch].sum%=p;
    }
    return;
}
void pushdown_jia(long long id)
{
    if(c[id].lazy_jia&&c[id].l!=c[id].r)
    {
        long long lazy=c[id].lazy_jia;
        c[id].lazy_jia=0;
        c[lch].lazy_jia+=lazy;
        c[rch].lazy_jia+=lazy;
        c[lch].sum+=(c[lch].r-c[lch].l+1)*lazy;	
        c[rch].sum+=(c[rch].r-c[rch].l+1)*lazy;
        c[lch].sum%=p;
        c[rch].sum%=p;
    }
    return;
}
void add_jia(long long id,long long l,long long r,long long val)
{
    pushdown_cheng(id);
    pushdown_jia(id);
    if(c[id].l==l&&c[id].r==r)	
    {
        c[id].lazy_jia+=val;
        c[id].sum+=(r-l+1)*val;
        c[id].sum%=p;
        return;
    }
    long long mid=(c[id].l+c[id].r)/2;
    if(mid<l)
    {
        add_jia(rch,l,r,val);
   	 	c[id].sum=(c[lch].sum+c[rch].sum)%p; 
        return;
    }
    if(mid+1>r)
    {
        add_jia(lch,l,r,val);	
   	 	c[id].sum=(c[lch].sum+c[rch].sum)%p; 
        return;
    }
    add_jia(lch,l,mid,val);
    add_jia(rch,mid+1,r,val);
   	c[id].sum=(c[lch].sum+c[rch].sum)%p; 
    return;
}
void add_cheng(long long id,long long l,long long r,long long val)
{
    pushdown_cheng(id);
    pushdown_jia(id);
    if(c[id].l==l&&c[id].r==r)	
    {
        c[id].lazy_cheng*=val;
        c[id].sum*=val;
        c[id].sum%=p;
        c[id].lazy_jia*=val;
        return;
    }
    long long mid=(c[id].l+c[id].r)/2;
    if(mid<l)
    {
        add_cheng(rch,l,r,val);
 	   	c[id].sum=(c[lch].sum+c[rch].sum)%p; 
        return;
    }
    if(mid+1>r)
    {
        add_cheng(lch,l,r,val);	
   		c[id].sum=(c[lch].sum+c[rch].sum)%p; 
        return;
    }
    add_cheng(lch,l,mid,val);
    add_cheng(rch,mid+1,r,val);
    c[id].sum=(c[lch].sum+c[rch].sum)%p; 
    return;
}
long long ask(long long id,long long l,long long r)
{
    pushdown_cheng(id);
    pushdown_jia(id);
    if(c[id].l==l&&c[id].r==r)
        return c[id].sum%p;
    long long mid=(c[id].l+c[id].r)/2;
    if(mid<l)
        return ask(rch,l,r)%p;
    if(mid+1>r)
        return ask(lch,l,r)%p;
    return (ask(lch,l,mid)+ask(rch,mid+1,r))%p;
}
int main()
{
    cin>>n>>m>>p;
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
            add_cheng(1,x,y,k);
        }
        if(pan==2)
        {
            cin>>x>>y>>k;
            add_jia(1,x,y,k);
        }
        if(pan==3)
        {
        	cin>>x>>y;
            cout<<ask(1,x,y)%p<<endl;
        }
    }
    return 0;
}	
