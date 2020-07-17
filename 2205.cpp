#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int jia,min=10000000,zong,shu,liang;
	for(int i=1;i<=3;i++)
	{
		cin>>shu>>jia;
		liang=ceil(n*1.0/shu);
		zong=liang*jia;
		if(zong<min)
			min=zong;
	}
	cout<<min;
	return 0;
} 
