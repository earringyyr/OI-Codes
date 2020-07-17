#include<iostream>
#include<cstdio>
using namespace std;
char a[30][30];
int n=1,m=1,ren[3],dox[5]={0,1,-1,0,0},doy[5]={0,0,0,1,-1},x,y;
void bfs()
{
	int head=0,tail=1,zou[10000][3];
	zou[1][1]=ren[1];	 
	zou[1][2]=ren[2];	//记录走的第一步 
	do
	{
		int pan=0;	//先表示为无路可走 
		head++;	 
		for(int i=1;i<=4;i++)	//枚举4条路 
		{
			x=zou[head][1]+dox[i];	 
			y=zou[head][2]+doy[i];	//临时记录走后的位置 
			if(x>=1&&x<=m&&y>=1&&y<=n&&(a[x][y]=='.'||a[x][y]=='*'))	//判断是否能走 
			{
				pan=1;	 //标记为有路可走 
				if(a[x][y]=='*')	//如果到达灵药 
				{
					cout<<head+1<<endl;	//输出步数 
					head=tail;
					break;	//退出深搜 
				}
				tail++;	 
				zou[tail][1]=x;
				zou[tail][2]=y;	//记录走的位置 
				a[x][y]='#';	//标记为走过了 
			}
		}
		if(pan==0)	//如果无路可走就输出-1 
		{
			cout<<-1<<endl;
			break;
		}
	}
	while(head<tail);
}
int main()
{	
	while(m!=0||n!=0)
	{
		cin>>m>>n;
		if(m!=0||n!=0)	//判断是否结束 
		{
			for(int i=1;i<=m;i++)
				for(int j=1;j<=n;j++)
				{
					cin>>a[i][j];	//读入迷阵 
					if(a[i][j]=='@')	//寻找起始位置 
					{
						ren[1]=i;	
						ren[2]=j;	//保存起始位置 
					}
				}
			bfs();	//广搜 
		}
	}
	return 0;
}
