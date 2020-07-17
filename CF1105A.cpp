#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,a[1005],ans=1000000000,qwq,sum;
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=100;++i)
    {
        sum=0;
        for(int j=1;j<=n;++j)
            sum+=min(abs(i-a[j]),min(abs(i+1-a[j]),abs(i-1-a[j])));
        if(sum<ans)
        {
            ans=sum;
            qwq=i;
        }
    }
    cout<<qwq<<" "<<ans;
    return 0;
}