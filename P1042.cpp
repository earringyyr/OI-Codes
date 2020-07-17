#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
char a[10000000];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int sum=0,hua=0,dui=0;
	while(cin>>a[++sum])
	{
		if(a[sum]=='E')
			break;
		if(a[sum]=='W')
			hua++;
		if(a[sum]=='L')
			dui++;
		if((hua>=11||dui>=11)&&abs(hua-dui)>=2)
		{
			cout<<hua<<":"<<dui<<endl;
			hua=0;
			dui=0;
		}
	}
	cout<<hua<<":"<<dui<<endl;
	cout<<endl;
	hua=0;
	dui=0;
	for(int i=1;i<=sum;i++)
	{
		if(a[i]=='W')
			hua++;
		if(a[i]=='L')
			dui++;
		if((hua>=21||dui>=21)&&abs(hua-dui)>=2)
		{
			cout<<hua<<":"<<dui<<endl;
			hua=0;
			dui=0;
		}
	}
	cout<<hua<<":"<<dui<<endl;
	return 0;
}
