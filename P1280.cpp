#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int f[10001],thing[10001];
struct node
{
	int p;
	int t;
}a[10001];
bool camp(node a,node b)
{
	return a.p>b.p; 
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		cin>>a[i].p>>a[i].t;
		a[i].t=a[i].p+a[i].t;
		thing[a[i].p]=1;
	}
	sort(a+1,a+k+1,camp);
	for(int i=n;i>=1;i--)
	{
		if(thing[i]==0)
		{
			f[i]=f[i+1]+1;
		}
		else
		{
			for(int j=1;j<=k;j++)
			{
				if(a[j].p==i)
				{
					f[i]=max(f[i],f[a[j].t]);
				}
			//	else	
			//	{
			//		break;
			//	}
			}
		}
	}
//	for(int i=1;i<=n;i++)
//		cout<<f[i]<<endl;
	cout<<f[1];
	return 0;
} 
