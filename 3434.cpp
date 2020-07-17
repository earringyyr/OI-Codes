#include<bits/stdc++.h>
using namespace std;
int n,into[30],b[30][30],c[30][30],use[30],ans[30];
struct node
{
	int x;
	int xx;
	int y;
	int yy;
}a[30];
bool tuopu()
{
	int sum=0;
	while(sum<n)
	{
		int t=0;
		for(int i=1;i<=n;++i)
			if(into[i]==1)
			{
				sum++;
				t++;
				int len=-1;
				for(int j=1;j<=b[i][0];++j)
					if(use[b[i][j]]==0)
						for(int k=1;k<=c[b[i][j]][0];++k)
							if(c[b[i][j]][k]==i)
							{
								len=j;
								use[b[i][j]]=1;
								break;
							}
				if(len!=-1)
				{
					ans[b[i][len]]=i;
					for(int j=1;j<=c[b[i][len]][0];++j)
						into[c[b[i][len]][j]]--;
				}
			}
		if(t==0)
			return false;
	}
	return true;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].x>>a[i].xx>>a[i].y>>a[i].yy;
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		for(int j=1;j<=n;++j)
			if(x>=a[j].x&&x<=a[j].xx&&y>=a[j].y&&y<=a[j].yy)
			{
				b[i][++b[i][0]]=j;
				c[j][++c[j][0]]=i;
				into[i]++;
			}
	}
	if(tuopu())
	{
		for(int i=1;i<n;++i)
			cout<<char('A'+i-1)<<" "<<ans[i]<<endl;
		cout<<char('A'+n-1)<<" "<<ans[n];
	}
	else
		cout<<"None";
	return 0;
}
