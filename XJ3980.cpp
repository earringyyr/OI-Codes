#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, k, p;
int a[405];
int sum[160005];
int f[405][160005];
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
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    if (p > n * n)
    {
        printf("%d", 0);
        return 0;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        sum[0] = f[i - 1][0];
        for (int j = 1; j <= p; ++j)
            sum[j] = (sum[j - 1] + f[i - 1][j]) % mod;
        if (i < k)
        {
            f[i][0] = (ll)f[i - 1][0] * i % mod;
            continue;
        }
        int maxn = min(k, i - k + 1);
        for (int j = 1; j <= p; ++j)
        {
            int l = max(0, j - maxn), r = j - 1;
            f[i][j] = (f[i][j] + (sum[r] - (l == 0 ? 0 : sum[l - 1]) + mod) % mod * 2 % mod) % mod;
            if (j >= maxn)
                f[i][j] = ((f[i][j] + (ll)f[i - 1][j - maxn] * (i - maxn * 2) % mod) % mod + mod) % mod;
        }
    }
    printf("%d", f[n][p]);
    return 0;
}