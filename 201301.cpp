#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","W",stdout);
	int n,x,ji=0;
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		if(i%10==x)
			ji++;
		if(i%100/10==x&&i>=10)
			ji++;
		if(i%1000/100==x&&i>=100)
			ji++;
		if(i%10000/1000==x&&i>=1000)
			ji++;
		if(i%100000/10000==x&&i>=10000)
			ji++;
		if(i%1000000/100000==x&&i>=100000)
			ji++;
	}
	cout<<ji;
	return 0;
}
