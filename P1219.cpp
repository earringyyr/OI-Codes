#include<iostream>
#include<cstdio>
using namespace std;
int n,num=0,l[14],xie[26],xia[26],a[14];
void print()
{
	for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
void search(int k)
{
	if(k==n+1)
	{
		num++;
		if(num<=3)
			print();
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(l[i]==0&&xie[k+i]==0&&xia[k-i+n]==0)
		{
			l[i]=1;
			xie[k+i]=1;
			xia[k-i+n]=1;
			if(num<=3)
			{
				a[k]=i;
			}
			search(k+1);
			l[i]=0;
			xie[k+i]=0;
			xia[k-i+n]=0;
		}
	}
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n;
	search(1);
	cout<<num;
	return 0;
}
