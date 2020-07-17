#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int x,y;
}app[5001];//用来记录每一个苹果的高度和所费力气 
bool camp(node a,node b)
{
	return a.y<b.y;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,s,a,b,hi,x,y,sum=0,ans=0;//sum表示数组中存入的苹果的个数 
	cin>>n>>s>>a>>b;
	hi=a+b;//记录能拿到的苹果的最高高度
	for(int i=1;i<=n;i++)
	{
		cin>>x>>y;
		if(x<=hi)//如果可以拿到苹果，则存入到数组当中 
		{
			app[++sum].x=x;
			app[sum].y=y;
		} 
	} 
	sort(app+1,app+sum+1,camp);//将耗费的力气从小到大排序
	int i=0;//表示当前枚举到了第几个苹果 
	while(s>0)
	{
		s-=app[++i].y;//将剩余力气减去摘这个苹果需要的力气 
		if(s>=0)//如果可以摘到这个苹果，那么将ans++ 
			ans++;
	} 
	cout<<ans;
	return 0;
} 
