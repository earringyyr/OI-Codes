#include<iostream>
#include<cstdio>
using namespace std;	
int num[10]={6,2,5,5,4,5,6,3,7,6};
int nu(int k)
{
	int sum=0;
	if(k==0)
		return 6; 
	while(k!=0)
	{
		sum+=num[k%10];
		k=k/10;
	}
	return sum;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,ans=0;
	cin>>n;
	for(int i=0;i<=1000;i++)
		for(int j=0;j<=1000;j++)
			if(nu(i)+nu(j)+nu(i+j)+4==n)
				ans++;
	cout<<ans;
	return 0;
}
