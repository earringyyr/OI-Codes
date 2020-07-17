#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int wan[1001],dao[1001],last[1001],d[1001],t[10001],a[10001],b[10001],xia[1001];
int main()
{
	int ans=0,n,m,k;
	cin>>n>>m>>k;
	for(int i=2;i<=n;++i)
		cin>>d[i];
	for(int i=1;i<=m;++i)
	{
		cin>>t[i]>>a[i]>>b[i];
		last[a[i]]=max(last[a[i]],t[i]);
		xia[b[i]]++;
	}
	dao[1]=0;
	for(int i=2;i<=n;++i)
	{
		dao[i]=max(dao[i-1],last[i-1])+d[i];
		xia[i]+=xia[i-1];
	}
	for(int i=1;i<=m;++i)
		ans+=dao[b[i]]-t[i];
	while(k>0)
	{
		k--;
		memset(wan,0,sizeof(wan));
		wan[n-1]=n;
		for(int i=n-2;i>=1;--i)
			if(dao[i+1]>last[i+1])
				wan[i]=wan[i+1];
			else
				wan[i]=i+1;
		int ma=0,l;
		for(int i=1;i<n;++i)
			if(xia[wan[i]]-xia[i]>ma&&d[i+1]>0)
			{
				l=i;
				ma=xia[wan[i]]-xia[i];
			}
		ans-=ma;
		d[l+1]--;
		for(int i=l;i<=n;++i)
			dao[i]=max(dao[i-1],last[i-1])+d[i];
	}
	cout<<ans;
	return 0;
}
