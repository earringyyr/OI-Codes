#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int p,ans,sum;
int a[1000005];
map<int,int> num,wei;
int main()
{
	cin>>p;
	ans=p;
	for(int i=1;i<=p;++i)
	{
		cin>>a[i];
		num[a[i]]++;
		wei[i]=a[i];
	}
	for(int i=1;i<=p;++i)
	{
		int ting;
		num[wei[i]]--;
		if(num[wei[i]]==0)
			break;
		sum=p-i;
		for(int j=p;j>=i;--j)
		{
			num[wei[j]]--;
			if(num[wei[j]]==0)
			{
				ting=j;
				break;
			}
			sum--;
		}
		if(sum<ans)
			ans=sum;
		for(int j=ting;j<=p;++j)
			num[wei[j]]++;
	}
	cout<<ans;
	return 0;
}
