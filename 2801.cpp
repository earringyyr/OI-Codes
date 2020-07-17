#include<iostream>
#include<cstdio>
using namespace std;
int migong[5][5];
int head=0,tail=1,wei,dox[3]={0,0,1},doy[3]={0,1,0},x,y,ax[10000][3];
void print(int a,int b)
{
	for(int i=1;i<=a;i++)
	{
		cout<<"("<<ax[a][1]<<","<<ax[a][2]<<")";
	} 
}
void bfs()
{	
	do
	{
		head++;
		for(int i=1;i<=2;i++)
		{
			x=ax[head][1]+dox[i];
			y=ax[head][2]+doy[i];
			if(x>=0&&x<=4&&y>=0&&y<=4&&migong[x][y]==0)
			{
				tail++;
				ax[head+1][1]=x;
				ax[head+1][2]=y;
				if(x==4&&y==4)
				{
					print(head,tail);
					head=tail;
					break;
				}
			}
		}
	}
	while(head<tail);
}
int main()
{
	for(int i=0;i<=4;i++)
		for(int j=0;j<=4;j++)
			cin>>migong[i][j];
	bfs();
	return 0;
}
