#include<iostream>
#include<cstdio>
using namespace std;
int l,q;
char a[2005][2005];
int main()
{
	cin>>l>>q;
	for(int i=1;i<=l;++i)
			scanf("%s",a[i]+1);
	for(int tt=1;tt<=q;++tt)
	{
		int x,y,num1=-1,num2=-1;
		scanf("%d%d",&x,&y);
		for(int j=x;j>=1;--j)
		{
			if(x+x-j>l)
				break;
			if(a[j][y]!=a[x+x-j][y])
				break;
			num1+=2;
		}
		for(int j=y;j>=1;--j)
		{
			if(y+y-j>l)
				break;
			if(a[x][j]!=a[x][y+y-j])
				break;
			num2+=2;
		}
		printf("%d\n",max(num1,num2));
	}
	return 0;
}
