#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const double pai=M_PI;
int n,x1,yy1,x2,y2,x[10],y[10],use[10],ans=0x3f3f3f;
double r[10];
void dfs(int k)
{
    if(k==n+1)
    {
        double kk=0;
        for(int i=1;i<=n;++i)
            kk=(double)(kk+r[i]*r[i]*pai);
        if((int)((x2-x1)*(y2-yy1)-kk+0.5)<ans)
            ans=(int)((x2-x1)*(y2-yy1)-kk+0.5);
        return;
    }
    for(int i=1;i<=n;++i)                                                                             
        if(use[i]==0)
        {
        	int p=1;
        	for(int j=1;j<=n;++j)
        		if(use[j]==1&&sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))<=r[j])
        		{
        			p=0;
        			break;
        		}
        	if(p!=0)
	        {
	            double mi=0x3f3f3f,num;
	            for(int j=1;j<=n;++j)
	                if(use[j]==1)
	                {
	                    num=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))-r[j];
	                    mi=min(mi,num);
	                }
	            use[i]=1;
	            mi=min(mi,(double)(x[i]-x1));
	      	    mi=min(mi,(double)(x2-x[i]));
	            mi=min(mi,(double)(y[i]-yy1));
	            mi=min(mi,(double)(y2-y[i]));
	            r[i]=mi;
        	}
        	else
        		r[i]=0;
            use[i]=1;
            dfs(k+1);
            use[i]=0;
        }
    return;
}
int main()
{
    cin>>n;
    cin>>x1>>yy1>>x2>>y2;
    if(x1>x2)
        swap(x1,x2);
    if(yy1>y2)
        swap(yy1,y2);
    for(int i=1;i<=n;++i)
        cin>>x[i]>>y[i];
    dfs(1);
    cout<<ans;
    return 0;
}
