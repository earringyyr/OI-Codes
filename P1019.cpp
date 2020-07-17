#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,use[21],ma=0,num;
string a[21];
char t;
void search(int k)
{
	int pan=1;
	for(int i=1;i<=n;i++)
	{
		if(use[i]<2)
		{
			for(int j=0;j<a[i].length();j++)
			{
				int sum=1;
				for(int x=0;x<=j;x++)
				{
					if(a[i][x]!=a[k][a[k].length()-1-j+x])	
						sum=0;
				}
				if(sum==1)
				{
					pan=0;
					num=num+a[i].length()-j-1;
					use[i]++;
					search(i);
					use[i]--;
					num=num+j-a[i].length()+1;
				}
			}
		}
	}
	if(pan==1)
	{
		if(num>ma)
			ma=num;
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>t;
	for(int i=1;i<=n;i++)
	{
		if(a[i][0]==t)
		{
			num=a[i].length();	
			use[i]++;
			search(i);
			if(num>ma)
				ma=num;
			memset(use,0,sizeof(use));
			num=0;
		}
	}
	cout<<ma;
	return 0;
}           	
