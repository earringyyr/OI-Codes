#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int a[200005];
int n,s,head,tail,p;
long long ans;
int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
	{
		if(a[i]==s&&(i==1||a[i-1]!=s))
		{ 
			head=i;
			p=1; 
		} 
		if(a[i]==s&&(i==n||a[i+1]!=s))
		{
			tail=i;
			break;
		}
	}
	int mid=n/2+1;
	if(p==0)
	{
		if(a[1]>s)
		{
			ans+=a[1]-s;
			a[1]=s;
			head=1;
			tail=1;
		}
		else
			if(a[n]<s)
			{
				ans+=s-a[n];
				a[n]=s;
				head=n;
				tail=n;
			}
			else
				for(int i=1;i<n;++i)
					if(a[i]<s&&a[i+1]>s)
					{
						if(abs(i-mid)<abs(i+1-mid))
						{
							ans+=s-a[i];
							a[i]=s;
							head=i;
							tail=i;
						}
						else
						{
							ans+=a[i+1]-s;
							a[i+1]=s;
							head=i+1;
							tail=i+1;
						}
						break;
					}
	}
	while(mid<head||mid>tail)
	{
		if(mid<head)
		{
			head--;
			ans+=s-a[head];
			a[head]=s;
		}
		if(mid>tail)
		{
			tail++;
			ans+=a[tail]-s;
			a[tail]=s;
		}
	}
	cout<<ans;
	return 0;
}
