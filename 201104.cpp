#include<iostream>
#include<cstdio>
using namespace std;
int l,ans=1,top=0;
char hao[100001],fu,lin;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","r",stdout);
	cin>>l;
	for(int i=1;i<=l;i++)
	{
		cin>>fu;
		if(fu=='+')
		{
			lin=2;
			for(;top>=1;top--)
			{
				if(hao[top]=='(')
					break;
				if(hao[top]=='+')
					break;
				if(hao[top]=='*')
				{
					lin*=2;
					lin=lin%10007;
				}
			}
			lin--;
			ans*=lin;
			ans=ans%10007;
			hao[++top]=fu;
		}
		if(fu=='*')
			hao[++top]='*';
		if(fu=='(')
			hao[++top]='(';
		if(fu==')')
		{
			hao[++top]=fu;
			while(hao[top]!='(')
			{
				top--;
				if(hao[top]=='*')
				{
					ans*=3;
					ans=ans%10007;
				}
			}
		}
	} 
	lin=2;
	for(int i=top;i>=1;i--)
	{
		if(hao[i]=='*')
		{
			lin*=2;
			lin=lin%10007;
			if(hao[i-1]!='*')
			{
				lin--;
				ans*=lin;
				ans=ans%10007;
			}
		}
		if(hao[i]=='+')
			lin=2;
	}
	cout<<ans;
	return 0;
} 
