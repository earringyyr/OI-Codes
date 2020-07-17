#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t,n,a[105],use[25005];
int main()
{
    scanf("%d",&t);
    for(int tt=1;tt<=t;++tt)
    {
        int ans=0;
        memset(use,0,sizeof(use));
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        for(int i=1;i<=n;++i)
            if(!use[a[i]])
            {
                ++ans;
                use[a[i]]=1;
                for(int j=1;j<=a[n];++j)
                    if(use[j])
                        for(int k=1;k<=(a[n]-j)/a[i];++k)
                            use[j+k*a[i]]=1;
            }
        cout<<ans<<endl;
    }
    return 0;
}