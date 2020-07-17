#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,f[201][201],m[101],t[101],p,q;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>p>>q;
	for(int i=1;i<=n;i++)
		cin>>m[i]>>t[i];
	for(int x=1;x<=n;x++)
	{
		for(int i=p;i>=0;i--)
		{
			for(int j=q;j>=0;j--)
			{
				if(i-m[x]>=0&&j-t[x]>=0)
					f[i][j]=max(f[i][j],f[i-m[x]][j-t[x]]+1);
			} 
		} 
	}
	cout<<f[p][q];
	return 0;
} 
