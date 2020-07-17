#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int x,y,x1,y1,dox[13]={0,2,2,-2,-2,1,1,-1,-1,2,2,-2,-2},doy[13]={0,-2,2,-2,2,2,-2,2,-2,1,-1,1,-1},qi[101][101];
int l[10001][4];
void zongshu(int d)
{
	int ji=0;
	while(d)
	{
		d=l[d][3];
		ji++;
	}
	cout<<ji<<endl;
}
void search(int p,int q)
{
	memset(l,0,sizeof(l));
	memset(qi,0,sizeof(qi));
	int head=0,tail=1,m,n;
	l[1][1]=p;
	l[1][2]=q;
	do
	{
		head++;
		for(int i=1;i<=12;i++)
		{
			m=l[head][1]+dox[i];
			n=l[head][2]+doy[i];
			if(m>=1&&m<=100&&n>=1&&n<=100&&qi[m][n]==0)
			{
				if(m==1&&n==1)
				{
					zongshu(head);
					return;
				}
				else
				{
					tail++;
					l[tail][1]=m;
					l[tail][2]=n;
					qi[m][n]=1;
					l[tail][3]=head;
				}
			}
		}
	}while(head<tail);
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>x>>y;
	cin>>x1>>y1;
	search(x,y);
	search(x1,y1);
	return 0;
} 
