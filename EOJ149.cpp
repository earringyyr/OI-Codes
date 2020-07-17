#include<iostream> 
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct node
{
	int ju;
	int x;
	int y;
}a[10005];
int m,n,x,y,num,sum,b[105][105];
bool comp(node c,node d)
{
	if(c.ju<d.ju)
		return 1;
	if(c.ju>d.ju)
		return 0;
	if(c.x<d.x)
		return 1;
	if(c.x>d.x)
		return 0;
	if(c.y<d.y)
		return 1;
	return 0;
}
int main()
{
	cin>>m>>n;
	cin>>x>>y;
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
		{
			cin>>b[i][j];
			if(i==x&&j==y)
				num=b[i][j];
		}
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			if(b[i][j]==num&&(i!=x||j!=y))
			{
				a[++sum].x=i;
				a[sum].y=j;
				a[sum].ju=abs(x-i)+abs(y-j);
			}
	sort(a+1,a+sum+1,comp);
	cout<<a[1].x<<" "<<a[1].y;
	return 0;
}
