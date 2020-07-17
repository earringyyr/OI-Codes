#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t=0,a[101];
void find(int k)
{
	int len=0;
	while(a[len]<=k)
		len++;
	len--;
	k-=a[len];
	cout<<2;
	if(len!=1)
		cout<<"(";
	if(len==0||len==2)
		cout<<len;
	else 
		if(len!=1)
			find(len);
	if(len!=1)
		cout<<")";
	if(k!=0)
	{
		cout<<"+";
		find(k);
	}
	return;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n;
	cin>>n;
	a[0]=1;
	for(int i=1;i<=100;i++)
		a[i]=a[i-1]*2;
	find(n);
	return 0;
}
