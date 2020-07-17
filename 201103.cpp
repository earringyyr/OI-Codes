#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int hao,s,w;
}a[200001];
bool camp(node a,node b)
{
	if(a.s>b.s)
		return 1;
	if(a.s<b.s)
		return 0;
	if(a.hao<b.hao)
		return 1;
	return 0;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,r,q;
	cin>>n>>r>>q;
	n*=2;
	for(int i=1;i<=n;i++)
	{
		a[i].hao=i;
		cin>>a[i].s;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w;
	}
	sort(a+1,a+n+1,camp);
	for(int i=1;i<=r;i++)
	{
		for(int i=1;i<n;i+=2)
		{
			if(a[i].w>a[i+1].w)
				a[i].s++;
			else
				a[i+1].s++;
		}
		sort(a+1,a+n+1,camp);
	}
	cout<<a[q].hao;
	return 0;
} 
