#include<iostream>
#include<cstdio>
using namespace std;
int n,a[10],num=0;
void search(int k)
{
	if(k==11)
	{
		if(n==0)
			num++;
		return;
	}
	for(int i=1;i<=3;i++)
	{
		n-=i;
		search(k+1);
		n+=i;
	}
}
void print()
{
	for(int i=1;i<=10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
void dfs(int k)
{
	if(k==11)
	{
		if(n==0)
			print();
		return;
	}
	for(int i=1;i<=3;i++)
	{
		n-=i;
		a[k]=i;
		dfs(k+1);
		n+=i;
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n;
	if(n<10||n>30)
		cout<<0;
	else
	{
		search(1);
		cout<<num<<endl;
		dfs(1);
	}
	return 0;
} 
