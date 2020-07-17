#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	char a,b,c,d;
	cin>>a>>b>>c>>d;
	if((a==b&&b==c)||(b==c&&c==d))
	{
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
}
