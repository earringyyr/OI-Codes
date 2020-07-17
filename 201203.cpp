#include<iostream>
#include<cstdio>
using namespace std;
int n,m,a[101],b[101],num=0;
void fangan(int k,int sum)
{
	if(k==m+1)
		num=(num+1)%1000007;
	else
	{
		for(int i=sum;i<=n;i++)
		{
			if(b[i]+1<=a[i])
			{
				b[i]++;
				fangan(k+1,i);
				b[i]--;
			}
		}
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	fangan(1,1);
	cout<<num;
	return 0;
}
