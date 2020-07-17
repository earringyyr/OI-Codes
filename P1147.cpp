#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int m;
	cin>>m;
	for(int i=1;i<m;++i)
	{
		int sum=0,k=i;;
		while(sum<m)
			sum+=k++;
		k--;
		if(sum==m)
			cout<<i<<" "<<k<<endl;
	}
	return 0;
}
