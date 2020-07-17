#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    double x,s,you=7,num=0;
    cin>>s>>x;
    if(s<x)
    {
    	if(x+s<7)
    		cout<<'n';
    	else
    		cout<<'y';
    	return 0;
    }
	while(num<s-x)
	{
		num+=you;
		you=you*98/100;
	}
	num+=you;
	if(num>s+x)
		cout<<'n';
	else
		cout<<'y';
    return 0;
}
