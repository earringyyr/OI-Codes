#include<iostream>
using namespace std;
int n,k,num=1,ans;
void search(int step)
{
	if(step==k)
	{
		if(n>=num)
			ans++;
		return;
	}
	for(int i=num;i<=n;i++)
	{
		n-=i;
		num=i;
		search(step+1);
		n+=i;
	}
	return;
}
int main()
{
	cin>>n>>k;
	search(1);
	cout<<ans;
	return 0;
}
