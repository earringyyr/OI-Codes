#include<iostream>
#include<cstdio>
using namespace std;
int ren[10000001]; 
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int m,n,head=1,tail;
	cin>>n>>m;
	tail=n;
	for(int i=1;i<=n;i++)
		ren[i]=i;
	tail=n;
	while(tail>head)
	{	
		for(int i=0;i<m;i++)
			ren[tail+i+1]=ren[head+i];
		tail=tail+m;
		head+=m+1;
	}
	cout<<ren[head];
	return 0;
}
