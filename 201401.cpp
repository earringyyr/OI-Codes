#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("suan.in","r",stdin);
	//freopen("suan.out","w",stdout);
	int n,num[1001],sum=0,a;
	bool shu[1001];
	memset(shu,true,sizeof(shu));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>num[i];
	}
	sort(num+1,num+n+1); 
	for(int i=1;i<=n-2;i++)
		for(int j=i+1;j<=n-1;j++)
		{
			for(int k=j+1;k<=n;k++)
				if(num[k]==num[i]+num[j])
				{
					if(shu[k]==true)
						sum++;
					shu[k]=false;
					break;
				}
		}
	cout<<sum;
	return 0;
}
