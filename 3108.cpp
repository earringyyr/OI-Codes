#include<iostream>
#include<cstdio>
using namespace std;
int a[2000],n,zou[2000];
bool panduan()
{
	int top=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=top)
		{ 
			top=a[i];
			zou[top]=0;
		}
		else
		{
			top--;
			while(zou[top]==0)
				top--;
			if(top!=a[i])
				return 0;
			else
				zou[a[i]]=0;
		}
	}
	return 1;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freoepn("a.out","w",stdout);
	cin>>n;
	for(int i=0;i<2000;i++)
		zou[i]=1;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	if(panduan())
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
