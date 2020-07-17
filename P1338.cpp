#include<iostream>
#include<cstdio>
using namespace std;
int n,m,head,tail,a[50005],ans[50005];
int main()
{
	cin>>n>>m;
	head=0;
	tail=n+1;
	for(int i=1;i<=n;++i)
	{
		if((long long)(n-i)*(n-i-1)/2>=m)
			ans[++head]=i;
		else
		{
			ans[--tail]=i;
			m-=n-i;
		}
	}
	for(int i=1;i<=n;++i)
		cout<<ans[i]<<" ";
	return 0;
}
