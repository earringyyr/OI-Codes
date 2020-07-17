#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,x;
	priority_queue<int,vector<int>,greater<int> > a;
	long long num=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		a.push(x);
	}
	while(a.size()>1)
	{
		int b=a.top(),c;
		a.pop();
		c=a.top();
		a.pop();
		a.push(b+c);
		num+=b+c;
	}
	cout<<num;
	return 0;
} 
