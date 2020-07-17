#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int m,n,ans=0,k,cun[101],top=0;
	for(int i=1;i<101;i++)
		cun[i]=-1;
	cin>>m>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k;
		int pan=0;
		for(int j=1;j<=m;j++)
			if(cun[j]==k)
				pan=1;
		if(pan==0)
		{
			top++;
			if(top==m+1)
				top=1;
			cun[top]=k;
			ans++;
		}
	} 
	cout<<ans;
	return 0;
}
