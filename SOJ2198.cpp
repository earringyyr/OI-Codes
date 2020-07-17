#include<iostream>
#include<cstdio>
#define eps 0.000001
using namespace std;
int n, l, r, a[100005], q[100005];
double lef, rig, sum[100005], num[100005];
bool check(double k)
{
	double ans=0;
	for(int i=1;i<=n;++i)
	{
		num[i]=a[i]-k;
		sum[i]=sum[i-1]+num[i];
	}
	int h=1, t=0;
	for(int i=1;i<=n;++i)
	{
		while(h<=t&&i-q[h]>r)
			++h;
		if(i>=l)
		{
			while(h<=t&&sum[q[t]]>sum[i-l])
				--t;
			q[++t]=i-l;
			ans=max(ans, sum[i]-sum[q[h]]);
		}
	}
	return ans>0;
}
int main()
{
	scanf("%d%d%d", &n ,&l, &r);
	for(int i=1;i<=n;++i)
	{
		scanf("%d", &a[i]);
		if(i==1)
			lef=rig=a[i];
		else
		{
			lef=min(lef, (double)a[i]);
			rig=max(rig, (double)a[i]);
		}
	}
	while(lef+eps<rig)
	{
		double mid=(lef+rig)/2;
		if(check(mid))
			lef=mid;
		else
			rig=mid;
	}
	printf("%.4f", lef);
	return 0;
}
