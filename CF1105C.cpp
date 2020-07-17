#include<iostream>
#include<cstdio>
using namespace std;
#define mod 1000000007
long long n,l,r,aa,bb,cc;
long long f[200005][3];
int main()
{
    cin>>n>>l>>r;
    if(l%3==2)
    {
        l++;
        bb++;
    }
    if(l%3==0)
    {
        l++;
        cc++;
    }
    if(r%3==2)
    {
        r--;
        bb++;
    }
    if(r%3==1)
    {
        r--;
        aa++;
    }
    aa+=(r-l+1)/3;
    bb+=(r-l+1)/3;
    cc+=(r-l+1)/3;
    f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        f[i][0]=((f[i-1][0]*cc)%mod+(f[i-1][1]*bb)%mod+(f[i-1][2]*aa)%mod)%mod;
        f[i][1]=((f[i-1][0]*aa)%mod+(f[i-1][1]*cc)%mod+(f[i-1][2]*bb)%mod)%mod;
        f[i][2]=((f[i-1][0]*bb)%mod+(f[i-1][1]*aa)%mod+(f[i-1][2]*cc)%mod)%mod;
    }
    cout<<f[n][0];
    return 0;
}