#include<iostream>
#include<cstdio>
using namespace std;
#define mod 1000000007
long long xx,yy,n,q,ma[500005],a[500005],b[500005],ans=1;
void exgcd(long long c,long long d)
{
	if(d==0)
	{
		xx=1;
		yy=0;
	}
	exgcd(d,c%d);
	long long lin=xx;
	xx=yy;
	yy=lin-c/d*yy;
	return;
}
int main()
{
	cin>>n>>q;
	for(long long i=1;i<=n;++i)
	{
		ma[i]=ma[i-1];
		scanf("%lld",&a[i]);
		if(a[i]>a[ma[i]])
			ma[i]=i;
	}
	for(long long i=1;i<=n;++i)
	{
		scanf("%lld",&b[i]);
		ans=(ans*min(b[i],a[ma[i]]))%mod;
	}
	for(long long i=1;i<=q;++i)
	{
		long long opt,x,y;
		scanf("%lld%lld%lld",&opt,&x,&y);
		if(opt==0)
		{
			for(long long j=x;j<=n&&a[ma[j]]<y;++j)
			{
				if(a[x]>b[j])
				{
					exgcd(min(a[ma[j]],b[j]),-mod);
					while(xx<0)
						xx+=mod;
					xx%=mod; 
					ans=(ans*xx)%mod;
					ans=(ans*y)%mod;
				}
				ma[j]=x;
			}
			a[x]=y;
		}
		else
		{
			if((a[x]>b[x]&&a[x]<y)||(a[x]<b[x]))
			{
				exgcd(min(a[x],b[x]),-mod);
				while(xx<0)
					xx+=mod;
				xx%=mod;
				ans=(ans*xx)%mod;
				ans=(ans*y)%mod;
			}
			b[x]=y;
		}
		cout<<ans<<endl;
	}
	return 0;
}
