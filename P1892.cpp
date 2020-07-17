#include<iostream>
#include<cstdio>
using namespace std;
int n,m,ans=0,father[1001],x,y,l[1001],f[1001][1001];
char a;
int getfather(int k)
{
    if(father[k]==k)
        return k;
    father[k]=getfather(father[k]);
    return father[k];
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        father[i]=i;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>x>>y;
        if(a=='F')
        {
            x=getfather(x),y=getfather(y);
            if(x!=y)
                father[x]=y;
        }
        else
        {
        	f[x][y]=1;
        	f[y][x]=1;
        	for(int i=1;i<=n;i++)
        	{
        		if(f[x][i]==1&&getfather(i)!=getfather(y))
        			father[getfather(i)]=getfather(y);
        		if(f[y][i]==1&&getfather(i)!=getfather(x))
        			father[getfather(i)]=getfather(x);		
        	}
        }
    }
    for(int i=1;i<=n;i++)
    {
    	l[getfather(i)]++;
    	if(l[getfather(i)]==1)
    		ans++;
    }
    cout<<ans;
    return 0;
}
