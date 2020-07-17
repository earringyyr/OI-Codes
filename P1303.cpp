#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("a.out","w",stdout);
	char a1[2001],b1[2001];
	int a[2001],b[2001],lena,lenb,c[20001]={0},lenc;
	scanf("%s%s",a1,b1);
	lena=strlen(a1);
	lenb=strlen(b1);
	for(int i=0;i<lena;i++)
		a[lena-i]=a1[i]-'0';
	for(int i=0;i<lenb;i++)
		b[lenb-i]=b1[i]-'0';
	for(int i=1;i<=lena;i++)
	{
		int x=0;
		for(int j=1;j<=lenb;j++)
		{
			c[i+j-1]=x+a[i]*b[j]+c[i+j-1];
			x=c[i+j-1]/10;
			c[i+j-1]%=10;
		}
		c[i+lenb]=x;
	}
	lenc=lena+lenb;
	while(c[lenc]==0&&lenc>1)
		lenc--;
	for(int i=lenc;i>=1;i--)
		cout<<c[i];
	return 0;
} 
