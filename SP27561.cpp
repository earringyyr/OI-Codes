#include<iostream>
using namespace std;
unsigned long long gcd(unsigned long long a,unsigned long long b)
{
	if(a%b==0)
		return b;
	return gcd(b,a%b);
}
int main()
{
	unsigned long long a,b,c;
	cin>>a>>b>>c;
	a=gcd(a,b);
	a=gcd(a,c);
	cout<<a;
	return 0;
} 
