#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int w;
	int hao;
}a[20001];
bool comp(node a,node b)
{
	if(a.w>b.w)
		return 1;
	if(a.w<b.w)
		return 0;
	if(a.hao<b.hao)
		return 1;
	return 0;
}
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,k,e[11];
	cin>>n>>k;
	for(int i=1;i<=10;i++)
		cin>>e[i];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w;
		a[i].hao=i;
	}
	sort(a+1,a+n+1,comp);
	for(int i=1;i<=n;i++)
	{
		a[i].w+=e[(i-1)%10+1];
	}
	sort(a+1,a+n+1,comp);
	for(int i=1;i<=k;i++)
		cout<<a[i].hao<<" ";
	return 0;
} 
