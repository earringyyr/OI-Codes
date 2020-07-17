#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,a[21],f[2001],b[21],last=0,num=0,ma=0;
void search(int k)
{
	if(k==m+1)
	{
		memset(f,0,sizeof(f));
		f[0]=1;
		for(int i=1;i<=n;i++)
		{
			if(b[i]==0)
			{
				for(int j=2000;j>=0;j--)
				{
					if(j+a[i]<=2000&&f[j]!=0)
					{
						f[j+a[i]]=1;
					}
				}
			}
		}
		num=0;
		for(int i=1;i<=2000;i++)
			if(f[i])
				num++;
		if(num>ma)
			ma=num;
		return;
	}
	for(int i=last+1;i<=n;i++)
	{
		b[i]=1;
		last=i;
		search(k+1);
		b[i]=0;
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	search(1);
	cout<<ma;
	return 0;
} 
