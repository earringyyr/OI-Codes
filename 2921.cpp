#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int p=1;
	char a[201],b[201];
	scanf("%s%s",a,b);
	int l,ll,f[201][201]={0};
	l=strlen(a);
	ll=strlen(b);
	if(a[0]==b[0])
		f[0][0]=1;
	for(int i=1;i<l;++i)
		if(a[i]==b[0])
			f[i][0]=1;
		else
			f[i][0]=f[i-1][0];
	for(int i=1;i<ll;++i)
		if(b[i]==a[0])
			f[0][i]=1;
		else
			f[0][i]=f[0][i-1];
	for(int i=1;i<l;++i)
		for(int j=1;j<ll;++j)
		{ 
			if(a[i]==b[j])
				f[i][j]=f[i-1][j-1]+1;
			else
				f[i][j]=max(f[i-1][j],f[i][j-1]);
		} 
	cout<<f[l-1][ll-1]<<endl;
	return 0;
}
