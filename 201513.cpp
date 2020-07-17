#include<iostream>
#include<cstdio>
using namespace std;
int color[100001],num[100001];
int main()
{
	//freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
	int n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>num[i];
	for(int i=1;i<=n;i++)
		cin>>color[i];
	for(int i=1;i<=n-2;i++)
		for(int j=i+2;j<=n;j+=2)
				if(color[i]==color[j])
					sum=(sum+(i+j)*(num[i]+num[j]))%10007;
	cout<<sum;
	return 0;
} 
