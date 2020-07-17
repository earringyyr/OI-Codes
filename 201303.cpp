#include<iostream>
#include<cstdio>
using namespace std;
int te[1000001],num[1000001],fen[1000001];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,p,max,sum;
	cin>>n>>p;
	for(int i=1;i<=n;i++)
	{
		cin>>num[i];
		if(i==1)
			te[i]=num[i];
		else
		{
			sum=num[i];
			for(int j=i-1;j>=1;j--)
			{
				if(num[j]<0)
					break;
				sum+=num[j];
			}
			if(sum>te[i-1])
				te[i]=sum;
			else
				te[i]=te[i-1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(i==1)
		{
			fen[i]=te[i];
			max=2*te[i];
		}
		else
		{
			if(te[i-1]+fen[i-1]>max)
				max=te[i-1]+fen[i-1];
			fen[i]=max;
		}
	}
	if(fen[n]+te[n]>max)
		max=fen[n]+te[n];
	if(max<fen[1])
		max=fen[1];
	cout<<max%p;
	return 0;
}
