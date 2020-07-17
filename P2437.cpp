#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,e[5001],g[5001],ans[5001];
string f[1001];
int main()
{
    //freopen("bea.in","r",stdin);
    //freopen("bea.out","w",stdout);
    for(int i=0;i<1001;i++)
    	f[i]="";
    int a,b;
    cin>>a>>b;
    f[a]="1";
    for(int j=a+1;j<=b;j++)
    {
    	memset(e,0,sizeof(e));
    	memset(g,0,sizeof(g));
    	memset(ans,0,sizeof(ans));
    	int len=max(f[j-1].length(),f[j-2].length());
    	for(int i=len-f[j-1].length()+1;i<=len;i++)
    	    e[i]=int(f[j-1][i-len+f[j-1].length()-1]-'0');
   		for(int i=len-f[j-2].length()+1;i<=len;i++)
    	    g[i]=int(f[j-2][i-len+f[j-2].length()-1]-'0');
        for(int i=len;i>=1;i--)
    	{
        	ans[i]=(e[i]+g[i])%10;
    	    e[i-1]+=(e[i]+g[i])/10;
	    }
		if(e[0]>0)
			f[j]+=char(e[0]+'0');
		for(int i=1;i<=len;i++)
			f[j]+=char(ans[i]+'0');
    }
    cout<<f[b]<<endl;
    return 0;
} 

