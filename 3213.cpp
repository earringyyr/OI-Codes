#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct node
{
	string xinxi;
	int parameter,priority,hao;
	friend bool operator< (node n1,node n2)
	{
		if(n1.priority>n2.priority)
			return 1;
		if(n1.priority<n2.priority)
			return 0;
		if(n1.hao>n2.hao)
			return 1;
		return 0;
	}
};
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	priority_queue<node> a;
	string b;
	int k=0;
	node c;
	while(cin>>b)
	{
		if(b=="PUT")
		{
			cin>>c.xinxi>>c.parameter>>c.priority;
			c.hao=++k;
			a.push(c);
		}
		if(b=="GET")
		{
			if(a.empty())
				cout<<"EMPTY QUEUE!"<<endl;
			else
			{	
				cout<<a.top().xinxi<<" "<<a.top().parameter<<endl;
				a.pop();
			}
		}
	}
	return 0;
}
