#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n;
	char chuan[400];
	cin>>n;
	int num=0,ma=0;
	scanf("%s",chuan); 
	int p=0;
	for(int i=0;i<n;i++)
	{
		if(chuan[i]!='w')
		{
			p=1;
			break;
		}
	}
	if(p==0)
	{
		cout<<n;
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		char len=chuan[i];
		if(len!='w')
		{
			num=0;
			int last;
			for(int j=i;;j--)
			{
				if(j==-1)
					j=n-1;
				last=i+1;
				if(i==n-1)
					last=0;
				if(chuan[j]!=len&&chuan[j]!='w')
				{
					last=j+1;
					if(j==n-1)
						last=0;
					break;
				}
				num++;
				if(j==last)
					break;
			}
			len=chuan[i+1];
			int kai;
			for(kai=i+1;;kai++)
			{
				if(kai==n)
					kai=0;
				if(chuan[kai]!='w')
				{
					len=chuan[kai];
					break;
				}
				num++;
			}
			for(int j=kai;;j++)
			{
				if(j==n)
					j=0;
				if(j==last)
					break;
				if(chuan[j]!=len&&chuan[j]!='w')
				{
					break;
				}
				num++;
			}
			if(num>ma)
				ma=num;
		}
	}
	cout<<ma<<endl;
	return 0;
}
