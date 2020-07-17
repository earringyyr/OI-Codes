#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("car.in","r",stdin);
	//freopen("car.out","w",stdout);
	double s,a,b,ans;
	cin>>s>>a>>b;
	ans=(2*a*s)/(3*a+b)/a+(s-(2*a*s)/(3*a+b))/b;
	printf("%.6f",ans);
	return 0;
} 
