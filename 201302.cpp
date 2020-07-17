#include<stack>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	char a;
	long long len=0,l,k,n1,n2;
	stack<long long> num;
	stack<char> hao;
	while(cin>>a)
//	{ 
//	for(int i=0;i<l;i++)
	{
		if(a>='0'&&a<='9')
		{
			if(len==0)
				num.push(int(a)-48);
			else
			{
				k=num.top()%10000;
				num.pop();
				num.push((k*10%10000+int(a)-48)%10000);
			}
			len=1;
		} 
		if(a=='+')
		{
			len=0;
			while(!hao.empty()&&hao.top()=='*')
			{
				n1=num.top()%10000;
				num.pop();
				n2=num.top()%10000;
				num.pop();
				num.push(n1*n2%10000);
				hao.pop();
	//			cout<<num.top()<<endl;
			}
			hao.push('+');
		}
		if(a=='*')
		{
			len=0;
			hao.push('*');
		}
	}
	while(!hao.empty())
	{
		if(hao.top()=='+')
		{
			n1=num.top()%10000;
			num.pop();
			n2=num.top()%10000;
			num.pop();
			num.push((n1+n2)%10000);
			hao.pop();
		//	cout<<num.top()<<endl;
		}
		if(!hao.empty()&&hao.top()=='*')
		{
			n1=num.top()%10000;
			num.pop();
			n2=num.top()%10000;
			num.pop();
			num.push(n1*n2%10000);
			hao.pop();
		//	cout<<num.top()<<endl;
		}
	}
	cout<<num.top()%10000;
//	}
	return 0;
} 
