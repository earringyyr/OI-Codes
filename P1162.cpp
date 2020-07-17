#include<iostream>
#include<cstdio>
using namespace std;
int n,tu[31][31],go[31][31],gox[5]={0,1,-1,0,0},goy[5]={0,0,0,1,-1},map[31][31];
void bfs(int x,int y)
{
    int l[9001][3],head=0,tail=1;
    l[1][1]=x;
    l[1][2]=y;
//	if(t!=1&&tu[x][y]==0)
//		map[x][y]=2;
	int pan=1;
    do
    {
        head++;
        for(int i=1;i<=4;i++)
        {
            x=l[head][1]+gox[i];
            y=l[head][2]+goy[i];
            if(x>=1&&x<=n&&y>=1&&y<=n&&go[x][y]==0&&tu[x][y]==tu[l[head][1]][l[head][2]])
            {
            //	if(t!=1&&tu[x][y]==0)
            //		map[x][y]=2;
                tail++;
                l[tail][1]=x;
                l[tail][2]=y;
                go[x][y]=1;
                if(x==1||x==n||y==1||y==n)
                	pan=0;
            }
        }
    }while(head<tail);
    if(pan==1)
    {
    	for(int i=1;i<=tail;i++)
    	{
    		map[l[i][1]][l[i][2]]=2;
    	}
    }
    return;
}
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>tu[i][j];
            map[i][j]=tu[i][j];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(go[i][j]==0)
            {
                go[i][j]=1;
                bfs(i,j);
            }
        }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<map[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
