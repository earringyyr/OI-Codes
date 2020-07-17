#include<iostream>
#include<cstdio>
using namespace std;
int gongyue(int a,int b)
{
	int min;
	if(a<b)
		min=a;
	else
		min=b;
	for(int i=min;i>=1;i--)
	{
		if(a%i==0&&b%i==0)
			return i;
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int a,b,l,k,min[3];
	double small=100000;
	cin>>a>>b>>l;
	k=gongyue(a,b);
	a=a/k;
	b=b/k;
	if(a<=l&&b<=l)
		cout<<a<<" "<<b;
	else
	{
		if(a<b)
		{
			for(int i=1;i<=l;i++)
				for(int j=i;j<=l;j++)
				{
					if(i*1.0/j>=a*1.0/b&&i*1.0/j-a*1.0/b<small)
					{
						small=i*1.0/j-a*1.0/b;
						min[1]=i;
						min[2]=j;
					}
				}
		}
		else
		{
			for(int i=1;i<=l;i++)
				for(int j=1;j<=i;j++)
				{
					if(i*1.0/j>=a*1.0/b&&i*1.0/j-a*1.0/b<small)
					{
						small=i*1.0/j-a*1.0/b;
						min[1]=i;
						min[2]=j;
					}
				}
		}
		cout<<min[1]<<" "<<min[2];
	}
	return 0;
}
