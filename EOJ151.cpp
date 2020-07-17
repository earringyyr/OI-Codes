#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n;
	while(cin>>n)
	{
		if(n<0)
			break;
		if(n==0)
		{
			cout<<"NO"<<endl;
			continue;
		}
		int num=1,sum=1,a[10000];
		a[0]=1;
		while(sum<=n)
		{
			a[num]=sum;
			num++;
			sum*=num;
		}
		num--;
		for(int i=num;i>=0;--i)
			if(n>=a[i])
				n-=a[i];
		if(n==0)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
