#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int use[1001];
struct node
{
	int dan[1001];
	int sum;
	int ben;
}a[1001];
bool camp(node a,node b)
{
	return a.sum>b.sum;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m;
	long long num=1;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int c,d;
		cin>>c>>d;
		a[c].dan[++a[c].sum]=d;
		a[d].dan[++a[d].sum]=c;
		a[c].ben=c;
		a[d].ben=d;
	}
	sort(a+1,a+n+1,camp);
	for(int i=1;i<=n;i++)
	{
		use[a[i].ben]=1;
		for(int j=1;j<=a[i].sum;j++)
		{
			if(use[a[i].dan[j]]==1)
				num*=2;
		}
	}
	cout<<num;
	return 0;
}
