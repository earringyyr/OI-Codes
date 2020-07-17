#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int len=0;
	char a;
	stack<int> b;
	while(cin>>a)
	{
		if(a=='@')
			break;
		else
		{
			int x;
			switch(a)
			{
				case '.':b.push(len); len=0; break;
				case '+':x=b.top(); b.pop(); x+=b.top(); b.pop(); b.push(x); break;
				case '-':x=b.top(); b.pop(); x=b.top()-x; b.pop(); b.push(x); break;
				case '*':x=b.top(); b.pop(); x*=b.top(); b.pop(); b.push(x); break;
				case '/':x=b.top(); b.pop(); x=b.top()/x; b.pop(); b.push(x); break;
				default: len=len*10+int(a-'0');
			}
		}
	}
	cout<<b.top();
	return 0;
}
