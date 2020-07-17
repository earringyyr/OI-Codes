#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[10001],b[10001],c[10001];
int l;
int wei;
void doit(int sx,int sy)
{
	if(sx==sy)
	{
		c[--wei]=b[sx];
		return;
	}
	if(sx>sy)
		return;
	int ax;
	int pan=1;
	for(int i=0;i<l;i++)
	{
		for(int j=sx;j<=sy;j++)
			if(a[i]==b[j])
			{
				ax=i;
				pan=0;
				break;
			}
		if(pan==0)
			break;
	}
	c[--wei]=a[ax];
	for(int i=sx;i<=sy;i++)
	{
		if(b[i]==a[ax])
		{
			doit(i+1,sy);
			doit(sx,i-1);
		}
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>a>>b;
	l=strlen(a);
	wei=l;
	for(int i=0;i<l;i++)
	{
		if(b[i]==a[0])
		{
			c[--wei]=a[0];
			doit(i+1,l-1);
			doit(0,i-1);
		}
	}
	for(int i=0;i<l;i++)
		cout<<c[i];
	return 0;

}
