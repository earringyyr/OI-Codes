#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int main()
{
	int n;
	cin>>n; 
	double f,a=1,b=1;
	for(int i=1;i<=n;i++)
		a*=(1+sqrt(5))/2;
	for(int i=1;i<=n;i++)
		b*=(1-sqrt(5))/2;
	f=(a-b)/sqrt(5);
	printf("%.2f",f);
	return 0;
}
