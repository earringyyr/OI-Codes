#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int l,r,ans=0;
	cin>>l>>r;
	for(int i=l;i<=r;i++)
	{
		if(i%10==2)
			ans++;
		if(i>=10&&i%100/10==2)
			ans++;
		if(i>=100&&i%1000/100==2)
			ans++;
		if(i>=1000&&i%10000/1000==2)
			ans++;
		if(i>=10000&&i%100000/10000==2)
			ans++; 
	}
	cout<<ans;
	return 0;
}
