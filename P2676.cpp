#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
bool camp(int a,int b)
{
	return a>b;
}
int main()
{
	//freopen("cow.in","r",stdin);
	//freopen("cow.out","w",stdout);
	int n,top=0,b,h[20001],s=0,num=0;
	cin>>n>>b;
	for(int i=1;i<=n;i++)
		cin>>h[i];
	sort(h+1,h+n+1,camp);
	while(s<b)
	{
		s+=h[++top];
		num++;
	}
	cout<<num;
	return 0;
}
