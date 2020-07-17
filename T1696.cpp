#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int use[11111111],d[11111112];
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    long long n,a,b,c,k,num=0,sum=0;
    cin>>n>>a>>b>>c;
    for(int i=1;i<=n;i++)
    {
    	k=(a*i*i+b*i+c)%11111111;
    	if(use[k]==0)
		{
			d[++sum]=k;
			use[k]=1;
		} 
	}
	sort(d+1,d+sum+1);
	for(int i=1;i<=sum;i++)
	{
		num=(num+i*d[i])%11111111;
	}
	cout<<num;
    return 0;
}
