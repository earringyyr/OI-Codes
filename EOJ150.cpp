#include<iostream>
#include<cstdio>
using namespace std;
int n,x[100],y[100],r[100],x1,y1,x2,y2,num;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>x[i];
	for(int i=1;i<=n;++i)
		cin>>y[i];
	for(int i=1;i<=n;++i)
		cin>>r[i];
	cin>>x1>>y1>>x2>>y2;
	for(int i=1;i<=n;++i)
	{
		int pan1=0,pan2=0;
		if((x1-x[i])*(x1-x[i])+(y1-y[i])*(y1-y[i])>r[i]*r[i])
			pan1=1;
		if((x2-x[i])*(x2-x[i])+(y2-y[i])*(y2-y[i])>r[i]*r[i])
			pan2=1;
		if((pan1==1&&pan2==0)|(pan1==0&&pan2==1))
			num++;
	}
	cout<<num;
	return 0;
}
