#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int l,n,ans1=0,ans2=0;
	cin>>l>>n;
	for(int i=1;i<=n;++i){
		int k;
		cin>>k;
		if(k<l+1-k)
		{
			ans1=max(k,ans1);
			ans2=max(ans2,l+1-k);
		}
		else
		{
			ans1=max(ans1,l+1-k);
			ans2=max(ans2,k);
		}
	}
	cout<<ans1<<" "<<ans2;
	return 0;
}
