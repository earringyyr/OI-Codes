#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int l;
	int r;
}a[2000005];
bool comp(node c,node d)
{
	if(c.l<d.l)
		return 1;
	if(c.l>d.l)
		return 0;
	if(c.r<d.r)
		return 1;
	return 0;
}
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int x,w;
		scanf("%d%d",&x,&w);
		a[i].l=x-w;
		a[i].r=x+w;
	}
	sort(a+1,a+n+1,comp);
	for(int i=n;i>=1;--i)
	{
		int len=i;
		ans++;
		while(i-1<=n&&a[len].l<a[i-1].r)
			--i;
	} 
	cout<<ans;
	return 0;
}
