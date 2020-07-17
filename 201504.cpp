#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int s;
	int a;
}p[100001];
bool camp(node a,node b)
{
	if(a.a+2*a.s>b.a)
		return 1;
	if(a.a<b.a)
		return 0;
	if(a.s>b.s)
		return 1;
	return 0;
}
int main()
{
	//freopen("salesman.in","r",stdin);
	//freopen("salesman.out","w",stdout);
	long long n,sum=0,pi=0,lu,max=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i].s;
	for(int i=1;i<=n;i++)
		cin>>p[i].a;
	sort(p+1,p+n+1,camp);
	for(int i=1;i<=n;i++)
	{
		sum++;
		pi+=p[sum].a;
		if(p[sum].s>max)
		{
			max=p[sum].s;
			lu=max*2;
		}	
		cout<<pi+lu<<endl;
	}
	return 0;
}
