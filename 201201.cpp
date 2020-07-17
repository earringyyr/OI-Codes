#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n;
	cin>>n;
	for(int i=2;i<n;i++)
	{
		if(n%i==0)
		{
			cout<<n/i;
			break;
		}
	}
	return 0;
} 
