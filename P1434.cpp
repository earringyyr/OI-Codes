#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int r,c;
int go[101][101],ma=1,num,s[101][101],a[101][101];
int gox[5]={0,0,0,1,-1},goy[5]={0,1,-1,0,0};
void search(int x,int y)
{
    for(int i=1;i<=4;i++)
    {
        int xx=x+gox[i],yy=y+goy[i];
        num++;
        if(xx>=1&&xx<=r&&yy>=1&&yy<=c&&go[xx][yy]==0&&num>s[xx][yy]&&a[x][y]>a[xx][yy])
        {
            s[xx][yy]=num;
            if(num>ma)
                ma=num;
            go[xx][yy]=1;
            search(xx,yy);
            go[xx][yy]=0;
        }
        num--;
    }
    return;
}
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    cin>>r>>c;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
        {
            cin>>a[i][j];
            s[i][j]=1;
        }
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
        {
            memset(go,0,sizeof(go));
            go[i][j]=1;
            num=1;
            search(i,j);
        }
    cout<<ma;
    return 0;
} 
