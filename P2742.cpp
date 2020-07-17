#include<iostream>
#include<cstdio>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;
int n,sum;
int mi=0,top;
struct node
{
    double x;
    double y;
}a[10005],s[10005];
double ans;
double ju(node aa,node bb,node cc)
{
    return ((aa.x-cc.x)*(aa.x-cc.x)+(aa.y-cc.y)*(aa.y-cc.y))-((bb.x-cc.x)*(bb.x-cc.x)+(bb.y-cc.y)*(bb.y-cc.y));
}
double jiao(node aa,node bb,node cc)
{
    return (aa.x-cc.x)*(bb.y-cc.y)-(bb.x-cc.x)*(aa.y-cc.y);
}
bool cmp(node aa,node bb)
{
    if(jiao(aa,bb,a[0])>0)
        return 1;
    if(jiao(aa,bb,a[0])==0&&ju(aa,bb,a[0]))
        return 1;
    return 0;
}
int main()
{
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>a[i].x>>a[i].y;
        if(a[i].y<a[mi].y||(a[i].y==a[mi].y&&a[i].x<a[mi].x))
            mi=i;
    }
    node lin=a[mi];
    a[mi]=a[0];
    a[0]=lin;
    sort(a+1,a+n,cmp); 
    s[0]=a[0];
    s[1]=a[1];
    s[2]=a[2];
    top=2;
    for(int i=3;i<n;++i)
    {
        while(top>1&&jiao(a[i],s[top],s[top-1])>0)
            top--;
        s[++top]=a[i];
    }
    for(int i=1;i<=top;++i)
        ans+=sqrt((s[i].x-s[i-1].x)*(s[i].x-s[i-1].x)+(s[i].y-s[i-1].y)*(s[i].y-s[i-1].y));
    ans+=sqrt((s[top].x-s[0].x)*(s[top].x-s[0].x)+(s[top].y-s[0].y)*(s[top].y-s[0].y));
    printf("%.2f",ans);
    return 0;
}
