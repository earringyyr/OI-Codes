#include<iostream>
#include<cstdio>
using namespace std;
long long n,l,sum[50005],c[50005],gg[50005],f[50005],ll[50005],head,tail;
long double xielv(long long j,long long jj)
{
	return (double)(f[jj]+gg[jj]-f[j]-gg[j])/(sum[jj]+jj-sum[j]-j);
}
int main()
{
	scanf("%lld%lld",&n,&l);
	for(long long i=1;i<=n;++i)
	{
		sum[i]=sum[i-1];
		scanf("%lld",&c[i]);
		sum[i]+=c[i];
		gg[i]=(sum[i]+i+l+1)*(sum[i]+i+l+1);
	}
	gg[0]=(l+1)*(l+1);
	for(long long i=1;i<=n;++i)
	{
		while(head<tail&&xielv(ll[head],ll[head+1])<=2*(sum[i]+i))
			head++;
		f[i]=f[ll[head]]+(sum[i]+i-sum[ll[head]]-ll[head]-l-1)*(sum[i]+i-sum[ll[head]]-ll[head]-l-1);
		while(head<tail&&xielv(ll[tail],i)<xielv(ll[tail-1],ll[tail]))
			tail--;
		ll[++tail]=i;
	}
	cout<<f[n];
	return 0;
}
