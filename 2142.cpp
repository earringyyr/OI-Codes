#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
void dao(char a1[],char b1[],int lena,int lenb)
{
	char c[10001];
	for(int i=0;i<lena;i++)
		c[i]=a1[i];
	for(int i=0;i<lenb;i++)
		a1[i]=b1[i];
	for(int i=0;i<lena;i++)
		b1[i]=c[i];
}
int main()
{
	//freopen("testdata.in","r",stdin);
	//freopen("testdata.out","w",stdout);
	char a1[10001],b1[10001];
	scanf("%s%s",a1,b1);
	int a[10001],b[10001],lena,lenb,c[10001],lenc;
	lena=strlen(a1);
	lenb=strlen(b1);
	if(lena<lenb)
	{
		cout<<'-';
		dao(a1,b1,lena,lenb);
		int lenc=lenb;
		lenb=lena;
		lena=lenc;
	}
	else
	{
		if(lena==lenb)
		{
			for(int i=0;i<lena;i++)
			{
				if(a1[i]>b1[i])
					break;
				if(b1[i]>a1[i])
				{
					cout<<'-';
					dao(a1,b1,lena,lenb);
					int lenc=lenb;
					lenb=lena;
					lena=lenc;
				}
			}
		}
	}
	lenc=lena;
	for(int i=0;i<lena;i++)	a[lena-i]=a1[i]-'0';
	for(int i=0;i<lenb;i++) b[lenb-i]=b1[i]-'0';
	for(int i=1;i<=lena;i++)
	{
		if(a[i]-b[i]<0)
		{
			a[i+1]--;
			a[i]+=10;
		}
		c[i]=a[i]-b[i];
	}
	while(c[lenc]==0&&lenc>1)
		lenc--;
	for(int i=lenc;i>=1;i--)
		cout<<c[i];
	return 0;
} 
