#include<iostream>
#include<cstdio>
using namespace std;
int n;
char k[4];
struct node
{
	char me;
	char fa;
	char ls;
	char rs;
}a[300];
void print(int d)
{
	if(a[d].me=='*')
		return;
	cout<<char(d);
	print(a[d].ls);
	print(a[d].rs);
}
int main()
{
	for(int i=0;i<300;i++)
	{
		a[i].me='*';
		a[i].fa='*';
		a[i].ls='*';
		a[i].rs='*';
	}
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char k;
		cin>>k;
		cin>>a[k].ls>>a[k].rs;
		a[k].me='0';
		a[a[k].ls].fa=k;
		a[a[k].rs].fa=k;
	}
	for(int i=0;i<300;i++)
	{
		if(a[i].me!='*'&&a[i].fa=='*')
		{
			print(i);
		}
	}
	return 0;
}
