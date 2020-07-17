#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int pan[401][401],num[401][401],gox[9]={0,2,2,1,1,-1,-1,-2,-2},goy[9]={0,1,-1,2,-2,2,-2,1,-1};
int head=0,tail=1,l[1600000][4];
int n,m,x,y;
int find(int d)
{
    int ans=0;
    while(d!=0)
    {
        ans++;
        d=l[d][3];
    }
    return ans-1;
}
void bfs()
{    
    l[1][1]=x;
    l[1][2]=y;
    l[1][3]=0;
    do
    {
        head++;
        for(int i=1;i<=8;i++)
        {
            x=l[head][1]+gox[i];
            y=l[head][2]+goy[i];
            if(x<=n&&x>=1&&y<=m&&y>=1&&pan[x][y]==0)
            {
                pan[x][y]=1;
                tail++;
                l[tail][1]=x;
                l[tail][2]=y;
                l[tail][3]=head;
                num[x][y]=find(tail);
            }
        }
    }
    while(head<tail);
}
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    memset(num,-1,sizeof(num));
    cin>>n>>m>>x>>y;
    num[x][y]=0;
    pan[x][y]=1;
    bfs();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            printf("%-5d",num[i][j]);
        cout<<endl;
    }
    return 0;
}
