#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct node
{
	int k,s;
}a[5001];
bool camp(node a,node b)
{
	if(a.s>b.s)
		return 1;
	if(a.s<b.s)
		return 0;
	if(a.k<b.k)
		return 1;
	return 0;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,m,score;
	cin>>n>>m;
	m=floor(m*1.5);
	for(int i=1;i<=n;i++)
		cin>>a[i].k>>a[i].s;
	sort(a+1,a+n+1,camp);
	score=a[m].s;
	while(a[m+1].s==score)
		m++;
	cout<<score<<" "<<m<<endl;
	for(int i=1;i<=m;i++)
		cout<<a[i].k<<" "<<a[i].s<<endl;
	return 0; 
}
