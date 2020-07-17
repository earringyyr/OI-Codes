#include<iostream>
#include<cstdio>
using namespace std;
int a[1000001];
struct node
{
    int a;
    int b;
}b[1000001];
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    int n,m,head=1,top=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
		cin>>a[i]; 
    for(int i=1;i<=m;i++)
    {
        while(head<=top&&b[top].a>=a[i])
            top--;
        b[++top].a=a[i];
        b[top].b=i;
    }
    cout<<b[head].a<<endl;
    for(int i=m+1;i<=n;i++)
    {
        while(head<=top&&b[head].b<=i-m)
            head++;
        while(head<=top&&b[top].a>=a[i])
            top--;
        b[++top].a=a[i];
        b[top].b=i;
        cout<<b[head].a<<endl;
    }
    return 0;
}
