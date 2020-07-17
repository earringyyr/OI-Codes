#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int t,k=0,l=0;
	long long qian=0;
	cin>>t;
	while(k+(++l)<t)
	{
		k+=l;
		qian+=l*l;
	}
	qian+=(t-k)*l;
	cout<<qian;
	return 0;
} 
