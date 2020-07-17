#include<iostream>
using namespace std;
int main()
{
	int n,ma=1,a[10001];
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		int num=1;
		for(int j=i+1;j<=n;j++)
		{
			if(a[j]==a[j-1]+1)
				num++;
			else
			{
				i=j-1;
				break;
			}
		}
		if(num>ma)
			ma=num;
	}
	cout<<ma;
	return 0;
}
