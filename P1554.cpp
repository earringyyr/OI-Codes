#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int num[10]={0},f[11]={0},m=0,n;
	char a[11];
	scanf("%s",a);
	cin>>n;
	f[0]=strlen(a);
	for(int i=0;i<f[0];++i)
		m=m*10+int(a[i]-'0');
	for(int i=10;i>=10-f[0]+1;--i)
		f[i]=int(a[i+f[0]-10-1]-'0');
	for(int j=m;j<=n;++j)
	{
		for(int i=10;i>=10-f[0]+1;--i)
			num[f[i]]++;
		f[10]++;
		for(int i=10;i>=10-f[0]+1;--i)
		{
			f[i-1]+=f[i]/10;
			f[i]=f[i]%10;
		}
		if(f[10-f[0]]!=0&&10-f[0]!=0)
			f[0]++;
	}
	for(int i=0;i<=9;++i)
		cout<<num[i]<<" ";
	return 0;
}
