#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long a,b,c,t1,t2;
	char aa;
	cin>>a>>aa>>b>>aa>>c;
	t1=a*3600+b*60+c;
	cin>>a>>aa>>b>>aa>>c;
	t2=a*3600+b*60+c;
	long long num;
	cin>>num;
	cout<<(t2-t1)*num;
	return 0;
}
