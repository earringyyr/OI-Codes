#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int p,k,s,f[300][50],num[300][300];
char a[300];
string b[7];
int main()
{
	cin>>p>>k;
	p*=20;
	for(int i=1;i<=p;++i)
		cin>>a[i];
	cin>>s;
	for(int i=1;i<=s;++i)
		cin>>b[i];
	for(int j=p;j>=1;--j)
		for(int i=j;i>=1;--i)
		{
			num[i][j]=num[i+1][j];
			string pan="";
			bool p=true;
			for(int m=i;m<=j&&p==true;++m)
			{
				pan+=a[m];
				for(int mm=1;mm<=s&&p==true;++mm)
					if(pan==b[mm])
					{
						num[i][j]++;
						p=false;
					}
			}
		}
/*	for(int i=1;i<=p;++i)
	{
		for(int j=i;j<=p;++j)
			cout<<num[i][j]<<" ";
		cout<<endl;
	}*/
	for(int i=1;i<=p;++i)
		for(int j=1;j<=min(i,k);++j)
			for(int n=j-1;n<i;++n)
				f[i][j]=max(f[i][j],f[n][j-1]+num[n+1][i]);
	cout<<f[p][k];
	return 0;
} 
