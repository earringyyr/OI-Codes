#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	long long b,k,p,left,result=1;
	cin>>b>>k>>p;
	cout<<b<<"^"<<k<<" mod "<<p<<"=";
	while(k>0)
	{
		if(k%2==1)
			result=result*b%p;
		k/=2;
		b=b*b%p;
	}
	cout<<result;
	return 0;
} 
