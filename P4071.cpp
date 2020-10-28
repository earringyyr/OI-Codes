#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, m, fac[1000005], inv[1000005], f[1000005];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int C(int a, int b)
{
    return (ll)fac[a] * inv[b] % mod * inv[a - b] % mod;
}
int main()
{
    fac[0] = 1;
    for (int i = 1; i <= 1000000; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[1000000] = ksm(fac[1000000], mod - 2);
    for (int i = 999999; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    f[0] = 1;
    for (int i = 2; i <= 1000000; ++i)
        f[i] = (ll)(i - 1) * (f[i - 1] + f[i - 2]) % mod;
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        printf("%d\n", (int)((ll)C(n, m) * f[n - m] % mod));
    }
    return 0;
}