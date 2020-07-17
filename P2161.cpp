#include<iostream>
#include<cstdio>
using namespace std;
#define lch id<<1
#define rch id<<1|1
int n,num,sum,use[200005];
struct node
{
    int l;
    int r;
    int num;
    int lazy;
}tr[400005];
void build(int id,int l,int r)
{
    tr[id].l=l;
    tr[id].r=r;
    if(l==r)
        return;
    int mid=(l+r)/2;
    build(lch,l,mid);
    build(rch,mid+1,r);
    return;
}
void pushdown(int id)
{
    if(tr[id].num!=-1&&tr[id].l!=tr[id].r)
    {
        tr[lch].num=tr[id].num;
        tr[rch].num=tr[id].num;
    }
    return;
}
void insert(int id,int l,int r,int w)
{
    pushdown(id);
    if(tr[id].num!=-1&&tr[id].l==l&&tr[id].r==r)
    {
        if(tr[id].num>0&&use[tr[id].num]==0)
        {
            num--;
            sum++;
            use[tr[id].num]=1;
        }
        tr[id].num=w;
        return;
    }
    int mid=(tr[id].l+tr[id].r)/2;
    if(mid>=r)
        insert(lch,l,r,w);
    if(mid+1<=l)
        insert(rch,l,r,w);
    if(mid>=l&&mid+1<=r)
    {
        insert(lch,l,mid,w);
        insert(rch,mid+1,r,w);
    }
    if((tr[id].l==tr[id].r)||(tr[lch].num!=-1&&tr[rch].num!=-1&&tr[lch].num==tr[rch].num))
        tr[id].num=tr[lch].num;
    else
        tr[id].num=-1;
    return;
}
int main()
{
    cin>>n;
    build(1,1,100005);
    for(int i=1;i<=n;++i)
    {
        char pan;
        cin>>pan;
        if(pan=='A')
        {
            sum=0;
            ++num;
            int s,e;
            cin>>s>>e;
            insert(1,s,e,i);
            cout<<sum<<endl;
        }
        else
            cout<<num<<endl;
    }
    return 0;
}