#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	char hao;
	int num;
}a[101];
bool camp(node a,node b)
{
	if(a.hao>b.hao)
		return 0;
	if(a.hao<b.hao)
		return 1;
	if(a.num<b.num)
		return 1;
	return 0;
}
int main()
{
	//freopen(j"a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,sum[10]={0};
	node queue[10][101];
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].hao>>a[i].num;
	}
	for(int i=1;i<=n;i++)
	{
		queue[a[i].num][++sum[a[i].num]]=a[i];
	}
	sort(a+1,a+n+1,camp);
	for(int i=1;i<=9;i++)
	{
		cout<<"Queue"<<i<<":";
		for(int j=1;j<=sum[i];j++)
			cout<<queue[i][j].hao<<queue[i][j].num<<" ";
		cout<<endl;
	}
	for(int i=1;i<=10;i++)
		sum[i]=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].hao=='A')
			queue[1][++sum[1]]=a[i];
		if(a[i].hao=='B')
			queue[2][++sum[2]]=a[i];
		if(a[i].hao=='C')
			queue[3][++sum[3]]=a[i];
		if(a[i].hao=='D')
			queue[4][++sum[4]]=a[i];
	}
	for(int i=1;i<=4;i++)
	{
		cout<<"Queue";
		if(i==1)	
			cout<<'A';
		if(i==2)
			cout<<'B';
		if(i==3)
			cout<<'C';
		if(i==4)
			cout<<'D';
		cout<<":";
		for(int j=1;j<=sum[i];j++)
			cout<<queue[i][j].hao<<queue[i][j].num<<" ";
		cout<<endl;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<a[i].hao<<a[i].num<<" ";
	}
	return 0;
} 
