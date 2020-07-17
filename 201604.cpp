#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
int a1[40001],b1[40001],c1[40001],d1[40001],x[40001],y[40001];
int main()
{
	//freopen("magic.in","r",stdin);
	//freopen("magic.out","w",stdout);
	int n,m,j;
	vector<int> k;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x[i];
		y[i]=x[i];
	}
	sort(x+1,x+m+1);
	for(int i=1;i<=m;i++)
	{
		if(x[i]!=x[i-1])
			k.push_back(x[i]);
	}
	j=k.size();
	for(int a=0;a<j-3;a++)
		for(int b=a+1;b<j-2;b++)
			for(int c=b+1;c<j-1;c++)
				for(int d=c+1;d<j;d++)
				{
					if((k[b]-k[a]==2*(k[d]-k[c]))&&(k[b]-k[a]<(k[c]-k[b])*1.0/3))
					{
						for(int i=1;i<=m;i++)
						{
							if(y[i]==k[a])
							{
								a1[i]++;
							}
						}
						for(int i=1;i<=m;i++)
						{
							if(y[i]==k[b])
							{
								b1[i]++;
							}
						}
						for(int i=1;i<=m;i++)
						{
							if(y[i]==k[c])
							{
								c1[i]++;
							}
						}
						for(int i=1;i<=m;i++)
						{
							if(y[i]==k[d])
							{
								d1[i]++;
								break;
							}
						}
					}
				}
	for(int i=1;i<=m;i++)
		cout<<a1[i]<<" "<<b1[i]<<" "<<c1[i]<<" "<<d1[i]<<endl;
	return 0;
} 
