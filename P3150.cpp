#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int m;
		cin>>m;
		if(m%2==0)
			cout<<"pb wins"<<endl;
		else
			cout<<"zs wins"<<endl; 
	}
	return 0;
}
