#include<iostream>
#include<cstdio>
using namespace std;
int n,q,a[1000001],b[1000001];
int lowbit(int x)
{
	return x&-x;
} 
void add(int x,int p)
{
	while(x<=n)
	{
		b[x]+=p;
		x+=lowbit(x);
	}
	return;
}
int ask(int x)
{
	int sum=0;
	while(x>=1)
	{
		sum+=b[x];
		x-=lowbit(x);
	}
	return sum; 
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=q;i++)
	{
		string pan;
		cin>>pan;
		if(pan=="FHYF**KZYJ")
		{
			int l,r,ll,w;
			cin>>l>>r>>w;
			if(l>r)
			{
				ll=r;
				r=l;
				l=ll;
			}
			add(l,w);
			add(r+1,-1*w);
		}
		else
		{
			int l,r,c,ll,num=0;
			cin>>l>>r>>c;
			if(l>r)
			{
				ll=r;
				r=l;
				l=ll;
			}
			for(int j=l;j<=r;j++)
			{
				if(a[j]+ask(j)>=c)
					num++;
			}
			cout<<num<<endl;
		}
	}
	return 0;
}
