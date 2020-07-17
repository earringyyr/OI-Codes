#include<iostream>
#include<cstdio>
using namespace std;
#define lch id*2
#define rch id*2+1
int m,d,num,a[200005],ans;
struct node
{
    int l;
    int r;
    int num;
}tr[1000005];
void build(int id,int l,int r)
{
    tr[id].l=l;
    tr[id].r=r;
    if(l==r)
    {
        tr[id].num=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(lch,l,mid);
    build(rch,mid+1,r);
    tr[id].num=max(tr[lch].num,tr[rch].num);
    return;
}
void add(int id,int wei,int val)
{
    if(tr[id].l==wei&&tr[id].r==wei)
    {
        tr[id].num=val;
        return;
    }
    int mid=(tr[id].l+tr[id].r)/2;
    if(wei<=mid)
        add(lch,wei,val);
    else
        add(rch,wei,val);
    tr[id].num=max(tr[lch].num,tr[rch].num);
    return;
}
int ask(int id,int l,int r)
{
    if(tr[id].l==l&&tr[id].r==r)
        return tr[id].num;
    int mid=(tr[id].l+tr[id].r)/2;
    if(r<=mid)
        return ask(lch,l,r);
    if(l>=mid+1)
        return ask(rch,l,r);
    return max(ask(lch,l,mid),ask(rch,mid+1,r));
}
int main()
{
    cin>>m>>d;
    build(1,1,m); 
    for(int i=1;i<=m;++i)
    {
        char pan;
        int n;
        cin>>pan;
        scanf("%d",&n);
        if(pan=='A')
        {
            int lin=(n+ans)%d;
            ++num;
            add(1,num,lin);
        }	
        else
        {
            ans=ask(1,num-n+1,num);
            printf("%d\n",ans);
        }
    }
    return 0;
}
