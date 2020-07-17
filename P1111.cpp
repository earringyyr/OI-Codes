#include<iostream>
#include<cstdio>
using namespace std;
int n,m,father[1001],righ=0,lef=0,pan=0;
struct node
{
	int x;
	int y;
	int t;
}a[100001];
int getfather(int d)
{
	if(father[d]==d)
		return d;
	father[d]=getfather(father[d]);
	return father[d];
}
bool find(int k)
{
	for(int i=1;i<=n;i++)
		father[i]=i;
	for(int i=1;i<=m;i++)
	{
		if(a[i].t<=k)
		{
			int x=getfather(a[i].x),y=getfather(a[i].y);
			if(x!=y)
				father[x]=y;
		}
	}
	int f=getfather(1);
	for(int i=1;i<=n;i++)
		if(getfather(i)!=f)
			return false;
	pan=1;
	return true;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].t;
		if(a[i].t>=righ)
			righ=a[i].t+1;
	}
	while(lef<righ)
	{
		int mid=(lef+righ)/2;
		if(find(mid))
			righ=mid;
		else
			lef=mid+1;
	}
	if(pan)
		cout<<lef;
	else
		cout<<-1;
	return 0;
}
