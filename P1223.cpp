#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int hao;
	int fen;
}t[1001];
bool camp(node a,node b)
{
	return a.fen<b.fen;
}
int main()
{
	//freopen("testdata (1).in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,a=0;
	double ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t[i].fen;
		t[i].hao=i;
	}
	sort(t+1,t+n+1,camp);
	for(int i=1;i<=n;i++)
		cout<<t[i].hao<<" ";
	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		ans+=t[i].fen*(n-i);
	}
	ans=ans/n;
	printf("%.2lf",ans);
	return 0;
}
