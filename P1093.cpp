#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int yu;
	int shu;
	int wai;
	int zong;
	int hao;
}a[301]; 
bool camp(node a,node b)
{
	if(a.zong>b.zong)
		return 1;
	if(a.zong<b.zong)
		return 0;
	if(a.yu>b.yu)
		return 1;
	if(a.yu<b.yu)
		return 0;
	if(a.hao<b.hao)
		return 1;
	return 0;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		a[i].hao=i;
		cin>>a[i].yu>>a[i].shu>>a[i].wai;
		a[i].zong=a[i].yu+a[i].shu+a[i].wai;
	}
	sort(a+1,a+n+1,camp);
	for(int i=1;i<=5;i++)
		cout<<a[i].hao<<" "<<a[i].zong<<endl;
	return 0;
}
