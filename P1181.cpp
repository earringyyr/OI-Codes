#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int a,n,m,sum=0,ans=1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(sum+a>m)
		{
			ans++;
			sum=0;
		}
		sum+=a;
	}
	cout<<ans;
	return 0;
} 
