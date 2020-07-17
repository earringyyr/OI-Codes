#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	int n,p=0,a[10005];
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		int j=i;
		while(j<=n&&a[j]==a[i])
			j++;
		j--;
		if(j-i+1>n/4)
		{
			cout<<a[i]<<endl;
			p=1;
		}
		i=j;
	}
	if(p==0)
		cout<<"No such person.";
	return 0;
}
