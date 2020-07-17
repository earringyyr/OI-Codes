#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int c;
	cin>>c;
	for(int x=1;x<=c;x++)
	{
		int n,ta[101][101]={0},f[101][101];
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)
				cin>>ta[i][j];
		for(int i=n-1;i>=1;i--)
		{
			for(int j=1;j<=i;j++)
			{
				ta[i][j]+=max(ta[i+1][j],ta[i+1][j+1]);
			}
		}
		cout<<ta[1][1]<<endl;
	}
	return 0;
}
