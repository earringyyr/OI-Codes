#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
bool camp(int a,int b)
{
	return a>b;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,c[100001],p[100001];
	long long sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>c[i];
	for(int i=1;i<=n;i++)
		cin>>p[i];
	sort(c+1,c+n+1);
	sort(p+1,p+n+1,camp);
	for(int i=1;i<=n;i++)
	{
		sum+=c[i]*p[i];
	}
	cout<<sum;
	return 0;
} 
