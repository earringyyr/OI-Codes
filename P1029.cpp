#include<iostream>
#include<cstdio>
using namespace std;
int gongyue(int x,int y)
{
	if(x%y==0)
		return y;
	return gongyue(y,x%y);
}
int main()
{
	int x,y,cheng,ans=0;
	cin>>x>>y;
	cheng=x*y;
	for(int i=1;i<=cheng;++i)
	{
		if(cheng%i!=0)
			continue;
		int p=i,q=cheng/i;
		if(gongyue(p,q)==x)
			ans++;
	}
	cout<<ans;
}
