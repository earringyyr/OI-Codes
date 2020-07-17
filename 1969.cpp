#include<iostream>
#include<cstdio>
using namespace std;
int n,h[1000000],ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>h[i];
		if(h[i]>h[i-1])
			ans+=h[i]-h[i-1];
	}
	cout<<ans;
	return 0;
}
