#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct zuobiao
{
    int a;
	int b;
}zuo[200001];
int n;
long long c[200001][3];
bool camp(zuobiao x,zuobiao y)
{
    return x.a<y.a;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>zuo[i].a>>zuo[i].b;
    sort(zuo+1,zuo+n+1,camp);
    for(int i=1;i<=n;i++)
    {
        c[i][1]=zuo[i].b;
        c[i][2]=1;
    }
    int l;
    for(int i=n-1;i>=1;i--)
    {
        l=0;
        for(int j=i+1;j<=n;j++)
            if(c[j][1]>c[i][1]&&c[j][2]>l)
                l=c[j][2];
        if(l>0)
            c[i][2]=l+1;
    }
    long long ma=-1;
    for(int i=1;i<=n;i++)
        if(c[i][2]>ma)
            ma=c[i][2];
    cout<<ma;
}
