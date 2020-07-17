#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> > a;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int k;
		cin>>k;
		if(k==1)
		{
			int x;
			cin>>x;
			a.push(x);
		}
		if(k==2)
			cout<<a.top()<<endl;
		if(k==3)
			a.pop();
	}
	return 0;
}
