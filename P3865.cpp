#include<iostream>
#include<cstdio>
using namespace std;
int lg[100005],a[100005][30],m,n;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i][0]);
	for(int i=1;i<=n;++i)
	{
		lg[i]=lg[i-1];
		if(1<<(lg[i]+1)==i)
			lg[i]++;
	}
	for(int i=n;i>=1;--i)
		for(int j=1;j<=lg[n-i+1];++j)
			a[i][j]=max(a[i][j-1],a[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=m;++i)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int k=lg[r-l+1];
		printf("%d\n",max(a[l][k],a[r-(1<<k)+1][k]));
	}
	return 0;
}
