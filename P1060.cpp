#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m,v,p,f[30001]={0};
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>v>>p;
		for(int j=n;j>=0;j--)
		{
			if(j+v<=n)
				f[j+v]=max(f[j+v],f[j]+v*p);
		}
	}
	cout<<f[n];
	return 0;
}
