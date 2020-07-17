#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	//freopen("median.in","r",stdin);
	//freopen("median.out","w",stdout);
	int w,n,b,a[100001],c[100001],num=0;
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==b)
		{
			w=i;
		}
	}
	for(int q=1;q<=n;q+=2)
	{
		int x=1,y=n-q+1;
		if(w-q+1>1)
			x=w-q+1;
		if(w+q-1<n-q+1)
			y=w+q-1;
		for(int i=x;i<=y;i++)
		{
			int sum=0;
			for(int j=i;j<=i+q-1;j++)
			{
				c[++sum]=a[j];
			}
			sort(c+1,c+sum+1);
			if(c[sum/2+1]==b)
				num++;
		}
	}
	cout<<num;
	return 0;
}
