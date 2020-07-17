#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct node
{
	int priority;
	int value;
	friend bool operator< (node n1,node n2)
	{
		if(n1.priority<n2.priority)
			return 1;
		if(n1.priority>n2.priority)
			return 0;
		if(n1.value>n2.value)
			return 1;
		return 0;
	}
};
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,yi,hao;
	priority_queue<node> a,b,c;
	node d;
	string k;
	while(cin>>n)
	{
		hao=0;
		for(int i=1;i<=n;i++)
		{
			cin>>k;
			if(k=="IN")
			{
				cin>>yi;
				if(yi==1)
				{
					cin>>d.priority;
					d.value=++hao;
					a.push(d);
				}
				if(yi==2)
				{
					cin>>d.priority;
					d.value=++hao;
					b.push(d);
				}
				if(yi==3)
				{
					cin>>d.priority;
					d.value=++hao;
					c.push(d);
				}
			}
			if(k=="OUT")
			{
				cin>>yi;
				if(yi==1)
				{
					if(a.empty())
						cout<<"EMPTY"<<endl;
					else
					{
						cout<<a.top().value<<endl;
						a.pop();
					}
				}
				if(yi==2)
				{
					if(b.empty())
						cout<<"EMPTY"<<endl;
					else
					{
						cout<<b.top().value<<endl;
						b.pop(); 
					}
				}
				if(yi==3)
				{
					if(c.empty())
						cout<<"EMPTY"<<endl;
					else
					{
						cout<<c.top().value<<endl;
						c.pop();
					}
				}
			}
		}
		int l;
		l=a.size();
		for(int i=1;i<=l;i++)
			a.pop();
		l=b.size();
		for(int i=1;i<=l;i++)
			b.pop();
		l=c.size();
		for(int i=1;i<=l;i++)
			c.pop();
	}
	return 0;
}
