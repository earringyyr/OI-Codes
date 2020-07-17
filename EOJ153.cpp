#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int n,a[10005];
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n/2;++i)
		a[i]=a[i]+a[n-i+1];
	sort(a+1,a+n/2+1);
	cout<<a[n/2];
	return 0;
}
