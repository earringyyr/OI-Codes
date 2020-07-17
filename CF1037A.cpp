#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,ans=1;
	cin>>n;
	while(n>1)
	{
		n/=2;
		ans++;
	}
	cout<<ans;
	return 0;
}
