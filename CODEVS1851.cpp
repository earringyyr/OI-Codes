#include <iostream>
#include <cstdio>
using namespace std;
#define mod 100003
long long m, n;
long long ksm(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b % 2 == 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return ans;
}
int main()
{
    scanf("%lld%lld", &m, &n);
    printf("%lld", ((ksm(m, n) - (long long)(ksm(m - 1, n - 1) * m)) % mod + mod) % mod);
    return 0;
}