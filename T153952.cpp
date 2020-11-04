#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 998244353, inv = 499122177;
int n, m, sum, cnt, tot, ans;
int pri[105], num[105];
int f[20005];
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
int main()
{
    scanf("%d%d", &n, &m);
    int sqr = sqrt(n);
    for (int i = 2; i <= sqr; ++i)
        if (n % i == 0)
        {
            pri[++sum] = i;
            while (n % i == 0)
            {
                n /= i;
                ++num[sum];
            }
        }
    (n > 1) && (pri[++sum] = n, num[sum] = 1);
    cnt = 1;
    for (int i = 1; i <= sum; ++i)
        cnt *= (num[i] + 1);
    ans = ksm(cnt, 2 * m);
    tot = 1;
    for (int i = 1; i <= sum; ++i)
    {
        memset(f, 0, 4 * m * num[i] + 4);
        f[0] = 1;
        for (int j = 1; j <= 2 * m; ++j)
            for (int k = m * num[i]; k >= 1; --k)
            {
                int minx = min(num[i], k);
                for (int l = 1; l <= minx; ++l)
                {
                    f[k] = f[k] + f[k - l];
                    (f[k] > mod) && (f[k] -= mod);
                }
            }
        tot = (ll)tot * f[m * num[i]] % mod;
    }
    ans = (ll)(ans + tot) * inv % mod;
    printf("%d", ans);
    return 0;
}