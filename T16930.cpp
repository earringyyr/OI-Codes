#include<iostream>
#include<cstdio>
using namespace std;
int x,y,z,m,c[4][23],num=0,use[23];
char a;
string b;
void search(int o,int v,int n)
{
    if(o==x+1&&v==y+1&&n==z+1)
    {
        num++;
        return;
    }
    if(o<=x)
    {
        for(int i=1;i<=m;i++)
        {
            if(use[i]==0&&c[1][i]==1)
            {
                use[i]=1;
                search(o+1,v,n);
                use[i]=0;
            }
        }
        return;
    }
    if(v<=y)
    {
        for(int i=1;i<=m;i++)
        {
            if(use[i]==0&&c[2][i]==1)
            {
                use[i]=1;
                search(o,v+1,n);
                use[i]=0;
            }
        }
        return;
    }
    if(n<=z)
    {
        for(int i=1;i<=m;i++)
        {
            if(use[i]==0&&c[3][i]==1)
            {
                use[i]=1;
                search(o,v,n+1);
                use[i]=0;
            }
        }
        return;
    }
}
int main()
{
    //freopen("football.in","r",stdin);
    //freopen("football.out","w",stdout);
    cin>>x>>a>>y>>a>>z;
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>b;
        if(b=="O")
            c[1][i]=1;
        if(b=="V")
            c[2][i]=1;
        if(b=="N")
            c[3][i]=1;
        if(b=="OV")
        {
            c[1][i]=1;
            c[2][i]=1;
        }
        if(b=="NV")
        {
            c[3][i]=1;
            c[2][i]=1;
        }
        if(b=="VON")
        {
            c[1][i]=1;
            c[2][i]=1;
            c[3][i]=1;
        }
    }
    search(1,1,1);
    cout<<num;
    return 0;
}
