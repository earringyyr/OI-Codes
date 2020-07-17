#include<iostream>
#include<cstdio>
using namespace std;
#define lch id<<1
#define rch (id<<1) | 1
int n,m,rr[1000005],d[1000005],s[1000005],t[1000005];
struct node
{
    int l;
    int r;
    int num;
    int lazy;
}tr[4000005];
inline void build(int id,int l,int r)
{
    tr[id].l=l;
    tr[id].r=r;
    if(l==r)
    {
        tr[id].num=rr[l];
        return;
    }
    int mid=(l+r)/2;
    build(lch,l,mid);
    build(rch,mid+1,r);
    tr[id].num=min(tr[lch].num,tr[rch].num);
    return;
}
inline void pushdown(int id)
{
    if(tr[id].l!=tr[id].r)
    {
        int lazy=tr[id].lazy;
        tr[id].lazy=0;
        tr[lch].lazy+=lazy;
        tr[rch].lazy+=lazy;
        tr[lch].num-=lazy;
        tr[rch].num-=lazy;
    }
    return;
}
inline void jian(int id,int l,int r,int val)
{
    pushdown(id);
    if(tr[id].l==l&&tr[id].r==r)
    {
        tr[id].num-=val;
        tr[id].lazy+=val;
        return;
    }
    int mid=(tr[id].l+tr[id].r)/2;
    if(r<=mid)
        jian(lch,l,r,val);
    if(l>=mid+1)
        jian(rch,l,r,val);
    if(l<=mid&&r>=mid+1)
    {
        jian(lch,l,mid,val);
        jian(rch,mid+1,r,val);
    }
    tr[id].num=min(tr[lch].num,tr[rch].num);
    return;
}
inline int ask(int id,int l,int r)
{
    pushdown(id);
    if(tr[id].l==l&&tr[id].r==r)
        return tr[id].num;
    int mid=(tr[id].l+tr[id].r)/2;
    if(r<=mid)
        return ask(lch,l,r);
    if(l>=mid+1)
        return ask(rch,l,r);
    return min(ask(lch,l,mid),ask(rch,mid+1,r));
}
inline int read()
{
    char x='=';
    while(x<'0'||x>'9')
        x=getchar();
    int y=0;
    while(x>='0'&&x<='9')
    {
        y=y*10+x-'0';
        x=getchar();
    }
    return y;
}
int main()
{
    n=read();
    m=read();
    for(int i=1;i<=n;++i)
        rr[i]=read();
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        d[i]=read();
        s[i]=read();
        t[i]=read();
    }
    for(int i=1;i<=m;++i)
    {
        if(ask(1,s[i],t[i])>=d[i])
            jian(1,s[i],t[i],d[i]);
        else
        {
            printf("-1\n%d",i);
            return 0;
        }
    }
    printf("0\n");
    return 0;
}