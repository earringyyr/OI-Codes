#include<bits/stdc++.h>
using namespace std;
int num=0,a[13],p=1,use[13],l[13][13];
int n,sum;
void search(int k)
{
    if(k==n+1)
    {
        if(num==sum)
        {
            for(int i=1;i<=n;i++)
                printf("%d ",a[i]);
       		exit(0);
        }
        return;
    }
    for(int i=1;i<=n;i++)
    {
    	if(use[i]==0)
    	{
    		use[i]=1;
    		a[k]=i;
    		num+=i*l[n][k];
    		if(num<=sum)
    			search(k+1);
    		num-=i*l[n][k];
    		use[i]=0;
    	}
    }
    return;
}
int main()
{
	scanf("%d%d",&n,&sum);
	for(int i=1;i<=n;i++)
		l[i][i]=l[i][1]=1;
    for(int i=3;i<=n;i++)
    	for(int j=2;j<n;j++)
    		l[i][j]=l[i-1][j-1]+l[i-1][j];
    search(1);
}
