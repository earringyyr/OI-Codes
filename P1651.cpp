#include<iostream>
#include<cstdio>
using namespace std;
int n,sum,h[100],f[55][500005];
int main()
{
	for(int i=0;i<55;++i)
		for(int j=0;j<500005;++j)
			f[i][j]=-500005;
	cin>>n;
	for(int i=1;i<=n;++i)
	{ 
		cin>>h[i];
		sum+=h[i];
	} 
	f[0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=sum;++j)
		{
			f[i][j]=max(f[i-1][j+h[i]],f[i-1][j]);
			if(h[i]<=j)
				f[i][j]=max(f[i][j],f[i-1][j-h[i]]+h[i]); 
			if(h[i]>=j)
				f[i][j]=max(f[i][j],f[i-1][h[i]-j]+j);
		}
	if(f[n][0]>0)
		cout<<f[n][0];
	else
		cout<<-1;
	return 0; 
} 
