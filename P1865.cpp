#include<iostream>
#include<cstdio>
using namespace std;
int n,m,sum[1000005],zhi[1000005],shu[1000005],num;
void find()
{
	for(int i=2;i<=m;++i)
	{
		sum[i]=sum[i-1];
		if(!shu[i])
		{
			zhi[++num]=i;
			shu[i]=i;
			sum[i]++;
		} 
		for(int j=1;j<=num&&zhi[j]<=shu[i]&&zhi[j]*i<=m;++j)
			shu[zhi[j]*i]=zhi[j];
	} 
	return;
}
int main()
{
	cin>>n>>m;
	find();
	for(int i=1;i<=n;++i)
	{
		int l,r;
		cin>>l>>r;
		if(l<1||r>m)
		{
			cout<<"Crossing the line"<<endl;
			continue;
		}
		cout<<sum[r]-sum[l-1]<<endl;
	}
	return 0;
}
