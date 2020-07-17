#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m;
int be[100],liv[100],num[100],pri[100];
string nam[100];
struct node
{
	int num;
	int pri;
	int be;
}a[100];
bool comp(node c,node d)
{
	if(c.pri<d.pri)
		return 1;
	if(c.pri>d.pri)
		return 0;
	if(c.be>d.be)
		return 1;
	if(c.be<d.be)
		return 0;
	if(c.num<d.num)
		return 1;
	return 0;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>be[i]>>liv[i]>>num[i]>>pri[i]>>nam[i];
	for(int j=1;j<=m;++j)
	{
		char bed;
		int sum,peo,ans=0;
		cin>>bed>>sum>>peo;
		for(int i=1;i<=n;++i)
		{
			int pan=0;
			if(bed=='A'&&be[i]>=20&&be[i]<=35)
				pan=1;
			if(bed=='B'&&be[i]>=36&&be[i]<=48)
				pan=1;
			if(bed=='C'&&be[i]>=49&&be[i]<=62)
				pan=1;
			if(pan==1)
			{
				int ren=min(liv[i],peo);
				if(ren*num[i]>=sum)
				{
					a[++ans].be=be[i];
					a[ans].num=i;
					a[ans].pri=ceil((double)sum/ren)*pri[i];
				}
			}
		}
		if(ans==0)
			cout<<"no-hotel"<<endl;
		else
		{
			sort(a+1,a+ans+1,comp);
			cout<<a[1].pri<<" "<<nam[a[1].num]<<endl;
		}
	}
	return 0;
}
