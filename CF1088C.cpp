#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,a[2005],cnt,sum=0,top,ans[2005][3];
int main()
{
    cin>>n;
    cnt=n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=n;i>=1;--i)
    {
        --cnt;
        a[i]=a[i]+sum;
        if(cnt>a[i])
        {
            sum+=cnt-a[i];
            ++top;
            ans[top][1]=cnt-a[i];
            ans[top][2]=i;
        }
        else
        {
            int k=cnt+n*ceil((double)(a[i]-cnt)/n)-a[i];
            if(k!=0)
            {
                ++top;
                sum+=k;
                ans[top][1]=k;
                ans[top][2]=i;
            }
        }
    }
    cout<<top+1<<endl;
    for(int i=1;i<=top;++i)
        cout<<1<<" "<<ans[i][2]<<" "<<ans[i][1]<<endl;
    cout<<2<<" "<<n<<" "<<n;
    return 0;
}