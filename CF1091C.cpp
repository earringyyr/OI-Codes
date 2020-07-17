#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
long long n,ans[100005],sum=0;
int main()
{
    cin>>n;
    for(register int i=1;i<=sqrt(n);++i)
        if(n/i*i==n)
        {
            ans[++sum]=(n-i+2)*(n/i)/2;
            ans[++sum]=(n-n/i+2)*i/2;
        }
    sort(ans+1,ans+sum+1);
    for(int i=1;i<=sum;++i)
        if(ans[i]!=ans[i-1])
            cout<<ans[i]<<" ";
    return 0;
}