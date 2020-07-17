#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,a[100000][3],l,max=0,k;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i][1];
		a[i][2]=1;
	}
	for(int i=n-1;i>=1;i--)
	{
		l=0;
		for(int j=i+1;j<=n;j++)
			if(a[j][1]>a[i][1]&&a[j][2]>=l)
				l=a[j][2];
		if(l>0)
			a[i][2]=l+1;
	}
	for(int i=1;i<=n;i++)
		if(a[i][2]>=max)
			max=a[i][2];
	cout<<max;
	return 0;
} 
