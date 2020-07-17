#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int t,m,f[1001][3]={0},a,b;
	cin>>t>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		for(int j=t;j>=0;j--)
		{
			if(f[j][1]+a<=t&&j+a<=t)
			{
				if(f[j][2]+b>=f[j+a][2])
				{
					f[j+a][2]=f[j][2]+b;
					f[j+a][1]=min(f[j+a][1],f[j][1]+a);
				}
			}
		}
	}
	cout<<f[t][2];
	return 0;
}
