#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
string a[21];
bool camp(string a,string b)
{
	int l=min(a.length(),b.length());
	for(int i=0;i<l;i++)
	{
		if(a[i]>b[i])
			return 1;
		if(a[i]<b[i])
			return 0;
	}
	if(a.length()>b.length())
	{
		for(int i=0;i<a.length()-l;i++)
		{
			if(a[i]>b[i+l])
				return 1;
			if(a[i]<b[i+l])
				return 0;
		}
	}
	if(a.length()<b.length())
	{
		for(int i=0;i<b.length()-l;i++)
		{
			if(a[i]>b[i+l])
				return 1;
			if(a[i]<b[i+l])
				return 0;
		}
	}
	return 0;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1,camp);
	for(int i=1;i<=n;i++)
		cout<<a[i];
	return 0;
}
