#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,use[16];
double num,mi=0x3f3f3f,x[16],y[16],xx,yy;
void search(int k)
{
	if(k==n+1)
	{
		mi=min(mi,num);
		return;
	}	
	for(int i=1;i<=n;i++)
	{
		if(use[i]==0)
		{
			double xxx=xx,yyy=yy;
			use[i]=1;
			double kk=sqrt((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i]));
			num+=kk;
			if(num>mi)
			{
				use[i]=0;
				num-=kk;
				continue;
			}
			xx=x[i];
			yy=y[i];
			search(k+1);
			use[i]=0;
			num-=kk;
			xx=xxx;
			yy=yyy;
		}
	}
	return;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	search(1);
	printf("%.2f",mi);
	return 0;
}
