#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long k,n,num=1,sum=1,a[200],ans=0,cnt=1,b[200];
	cin>>k>>n;
	while(sum<n){
		sum*=2;
		cnt*=k;
		a[++num]=sum;
		b[num]=cnt;
	}
	a[1]=1;
	b[1]=1;
	for(int i=num-1;i>=1;--i)
	{
		if(n==0)
			break;
		if(n>=a[i]){
			n-=a[i];
			ans+=b[i];
		}
	}
	cout<<ans;
	return 0;
}
