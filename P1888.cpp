#include<iostream>
#include<algorithm>
using namespace std;
int yue(int a,int b)
{
	if(a%b==0)	
	 	return b;
	return yue(b,a%b);
}
int main()
{
	int a[4];
	for(int i=1;i<=3;i++)
		cin>>a[i];
	sort(a+1,a+4);
	int chu=yue(a[1],a[3]);
	a[1]/=chu;
	a[3]/=chu;
	cout<<a[1]<<'/'<<a[3];
	return 0;
}
