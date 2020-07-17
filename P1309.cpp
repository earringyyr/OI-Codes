#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int num;
	int s;
	int w;
}a[200001];
int won[200001],lose[200001]; 
	node b[200001];
bool camp(node c,node d)
{
	if(c.s>d.s)
		return 1;
	if(c.s<d.s)
		return 0;
	if(c.num<d.num)
		return 1;
	return 0;
}
int main()
{
	int n,r,q;
	cin>>n>>r>>q;
	for(int i=1;i<=2*n;++i)
		cin>>a[i].s;
	for(int i=1;i<=2*n;++i)
	{
		cin>>a[i].w;
		a[i].num=i;
	}
	sort(a+1,a+2*n+1,camp);
	for(int x=1;x<=r;++x)
	{
		int summ=0;
		for(int i=1;i<=2*n;i+=2)
		{
			if(a[i].w>a[i+1].w)
			{
				won[++summ]=i;
				a[i].s++;
				lose[summ]=i+1;
			}
			else
			{
				won[++summ]=i+1;
				a[i+1].s++;
				lose[summ]=i;
			}
		}
		int l=1,r=1,sum=0;
		while(l<=summ||r<=summ)
		{
			if(l<=summ&&a[won[l]].s>a[lose[r]].s)
			{
				b[++sum].num=a[won[l]].num;
				b[sum].s=a[won[l]].s;
				b[sum].w=a[won[l]].w;
				l++;
			}
			else
			{
				if(l<=summ&&r<=summ&&a[won[l]].s==a[lose[r]].s)
				{
					if(a[won[l]].num<a[lose[r]].num)
					{
						b[++sum].num=a[won[l]].num;
						b[sum].s=a[won[l]].s;
						b[sum].w=a[won[l]].w;
						l++;
					}
					else
					{
						b[++sum].num=a[lose[r]].num;
						b[sum].s=a[lose[r]].s;
						b[sum].w=a[lose[r]].w;
						r++;
					}
				}
				else
				{
					b[++sum].num=a[lose[r]].num;
					b[sum].s=a[lose[r]].s;
					b[sum].w=a[lose[r]].w;
					r++;
				}
			}
		} 
		for(int i=1;i<=sum;++i)
		{
			a[i].num=b[i].num;
			a[i].s=b[i].s;
			a[i].w=b[i].w;
		}
	}
	cout<<a[q].num;
	return 0;
} 
