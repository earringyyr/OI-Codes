#include<iostream>
#include<cstdio>
using namespace std;
int n;
long long ans,sum[1000005],num[1000005];
int main()
{
    cin>>n;
    sum[1]=1;
    num[1]=n;
    for(int i=2;i<=n;++i)
    {
        sum[i]=sum[i-1]*i;
        sum[i]%=998244353;
        num[i]=num[i-1]*(n-i+1);
        num[i]%=998244353;
    }
    ans=sum[n];
    for(int i=1;i<=(n-1);++i)
    {
        ans+=((sum[i]-1)*num[n-i]%998244353);
        ans%=998244353;
    }
    cout<<ans;
    return 0;
}