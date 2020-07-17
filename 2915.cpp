#include<iostream>
#include<cstdio>
using namespace std;
int b[100000][4];
int main()
{
	int n=0,maxx=0,k=0,l=0,j;
	while(cin>>b[++n][1])
	{
		b[n][2]=1;
		b[n][3]=0;
	}
	n-=1;
	for(int i=n-1;i>=1;i--)
	{
		l=0;
		for(int j=i+1;j<=n;j++)
			if(b[j][1]>b[i][1]&&b[j][2]>=l)
			{
				l=b[j][2];
				k=j;
			}
		if(l>0)
		{
			b[i][2]=l+1;
			b[i][3]=k;
		}
	}
	for(int j=1;j<=n;j++)
		if(b[j][2]>=maxx)
		{
			maxx=b[j][2];
			k=j;
		}
	cout<<"max="<<maxx<<endl;
	while(k)
	{
		cout<<b[k][1]<<" ";
		k=b[k][3];
	}
	return 0;
}
