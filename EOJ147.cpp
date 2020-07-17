#include<iostream>
#include<cstdio>
using namespace std;
int n,m,ans;
long long daan=1;
void dfs(int num,int ma)
{
	if(num==n)
	{
		ans++;
		return;
	}
	for(int i=ma;i<=n-num;++i)
		dfs(num+ma,ma);
	return;
}
int main()
{
	cin>>n>>m;
	dfs(0,1);
	for(int i=1;i<=n;++i)
	{
		daan*=m;
		daan%=999999599;
	}
	cout<<daan;
	return 0;
}
