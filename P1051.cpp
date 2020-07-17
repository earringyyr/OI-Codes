#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,ans=0;
	struct node
	{
		string name;
		int mo;
		int ban;
		char xue;
		char xi;
		int lun;
		int num;
	}a[101];
	cin>>n;
	int ma=0;
	string ming;
	for(int i=1;i<=n;i++)
	{
		a[i].num=0;
		cin>>a[i].name>>a[i].mo>>a[i].ban>>a[i].xue>>a[i].xi>>a[i].lun;
		if(a[i].mo>80&&a[i].lun>=1)
			a[i].num+=8000;
		if(a[i].mo>85&&a[i].ban>80)
			a[i].num+=4000;
		if(a[i].mo>90)
			a[i].num+=2000;
		if(a[i].mo>85&&a[i].xi=='Y')
			a[i].num+=1000;
		if(a[i].ban>80&&a[i].xue=='Y')
			a[i].num+=850;
		ans+=a[i].num;
		if(a[i].num>ma)
		{
			ma=a[i].num;
			ming=a[i].name;
		}
	}
	cout<<ming<<endl<<ma<<endl<<ans;
	return 0;
} 
