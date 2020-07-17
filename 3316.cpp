#include<iostream>
#include<cstdio>
using namespace std;
struct tree
{
	int left;
	int right;
	int data;
}shu[32769];
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","W",stdout);
	int n;
	cin>>n;
	for(int i=0;i<=32769;i++)
	{
		shu[i].left=-1;
		shu[i].right=-1;
		shu[i].data=0;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>shu[i].data;
	}
	for(int i=1;i<=n;i++)
	{
		int level=0,child=0;
		while(child==0)
		{
			if(shu[i].data<shu[level].data)
			{
				if(shu[level].left!=-1)
				{
					level=shu[level].left;
				}
				else
				{
					shu[level].left=i;
					child=1;
				}
			}
			else
			{
				if(shu[level].right!=-1)
				{
					level=shu[level].right;
				}
				else
				{
					shu[level].right=i;
					child=1;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<shu[i].left<<' '<<shu[i].data<<' '<<shu[i].right<<endl;
	}
	return 0;
} 
