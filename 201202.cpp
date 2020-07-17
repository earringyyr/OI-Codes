#include<iostream>
#include<cstdio>
using namespace std;
int hao[10001][100],shu[10001];
bool go[10001][100]; 
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m,num=0,wei,sum;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=0;j<m;j++)
		{
			cin>>go[i][j]>>hao[i][j];
			if(go[i][j]==1)
				shu[i]++;
		}
	cin>>wei;
	for(int i=1;i<=n;i++)
	{
		num=(num+hao[i][wei])%20123;
		sum=hao[i][wei]%shu[i];
		if(sum==0)
			sum=shu[i];
		while(sum>0)
		{
			if(go[i][wei]==1)
				sum--;
			if(sum>0)
			{
				wei++;
				if(wei==m)
					wei=0;
			}
		}
	}
	cout<<num;
	return 0;
}
