#include<cstdio>
#include<iostream>
using namespace std;
int guo[100001]={0},time1[100001],k[100001],x[100001][30];
int main()
{
	//freopen("port.in","r",stdin);
	//freopen("port.out","w",stdout);
	long long n,top=1,top1,pan,sum=0,num=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		top1=top;
		pan=1;
		cin>>time1[i];
		while(time1[i]-time1[top]>=86400)
		{
			pan=0;
			top++;
		}
		for(int j=top1;j<top;j++)
		{
			for(int l=1;l<=k[j];l++)
			{
				guo[x[j][l]]--;
				if(guo[x[j][l]]==0)
					num--;
			}
		}
		cin>>k[i];
		for(int j=1;j<=k[i];j++)
		{
			cin>>x[i][j];
			guo[x[i][j]]++;
			if(guo[x[i][j]]==1)
				num++;
		}
		cout<<num<<endl;	
	}
	return 0;
} 
