#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[101],b[101];
int n,f[101][101];
int l,ll;
bool check(int s,int e)
{
	for(int i=s;i<=e;++i)
		if(a[i]!=b[i])
			return false;
	return true;
}
int main()
{
	for(int i=0;i<=100;++i)
		for(int j=0;j<=100;++j)
			f[i][j]=0x3f3f3f;
	scanf("%s",a);
	l=strlen(a);
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		scanf("%s",b);
		ll=strlen(b);
		for(int j=0;j<=l-ll;++j)
		{
			if(check(j,j+ll-1))
				f[j][j+ll-1]=1;
		}
	}
	for(int i=0;i<l;++i)
		for(int j=i+1;j<l;++j)
			for(int k=i;k<j;++k)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
	cout<<f[0][l-1];
	return 0;
} 
