#include<iostream>
#include<algorithm> 
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m,s[101],num,top,time=0,w[10001];
	cin>>n>>m;
	num=n;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i]; 
	} 
	top=m;
	for(int i=1;i<=m;i++)
	{
		s[i]=w[i];
	}
	while(num!=0)
	{
		time++;
		for(int i=1;i<=m;i++)
		{
			s[i]--;
			if(s[i]==0)
			{
				num--;
				if(top<n)
				{
					s[i]=w[++top];
				}
			}
		}
	}
	cout<<time;
	return 0;
} 
