#include<iostream>
#include<cmath>
using namespace std;
int num=0,m,a[1000001];
int main()
{
	cin>>m;
	while(m>1)
	{
		a[++num]=ceil(m*1.0/2);
		m=floor(m*1.0/2);
	}
	a[++num]=1;
	cout<<num<<endl;
	for(int i=num;i>=1;--i)
	cout<<a[i]<<" ";
	return 0;
}
