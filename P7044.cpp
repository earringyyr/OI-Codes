#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, k, num, cnt, sum, ans;
int fac[2000005], inv[2000005], c[2000005];
char s[1000005];
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
int C(int m, int n)
{
    if (m < n)
        return 0;
    return (ll)fac[m] * inv[n] % mod * inv[m - n] % mod;
}
int main()
{
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    fac[0] = 1;
    for (int i = 1; i <= n + k; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n + k] = ksm(fac[n + k], mod - 2);
    for (int i = n + k - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i <= n; ++i)
    {
        cnt = (cnt + C(k + i - 2, i - 1)) % mod;
        c[num + 1000000] = (c[num + 1000000] + C(k + i - 2, i - 1)) % mod;
        if (s[i] == '(')
        {
            sum = (sum + cnt) % mod;
            ++num;
        }
        else
        {
            sum = (sum - cnt + mod) % mod;
            sum = (sum + 2 * c[num + 1000000] % mod) % mod;
            --num;
            c[num + 1000000] = (c[num + 1000000] + c[num + 1000000 + 1]) % mod;
            c[num + 1000000 + 1] = 0;
        }
        ans = (ans + (ll)sum * C(k + n - i - 1, n - i) % mod) % mod;
    }
    printf("%d", ans);
    return 0;
}