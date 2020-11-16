#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, p, m, sum, pw, num = 1, ans;
int r[4005], g[4005];
int f[55][55][4005];
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
void ntt(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod;
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                ww = (ll)w * ww % mod;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod;
    }
    return;
}
void dfs(int k)
{
    if (k == 1)
    {
        ++sum;
        for (int i = 0; i <= min(m, 9); ++i)
            f[i % p][sum][i] = 1;
        pw = 10 % p;
        return;
    }
    dfs(k / 2);
    ++sum;
    for (int i = 0; i < p; ++i)
        ntt(f[i][sum - 1], 1);
    for (int k = 0; k < p; ++k)
        for (int l = 0; l < p; ++l)
        {
            for (int i = 0; i < num; ++i)
                g[i] = (ll)f[k][sum - 1][i] * f[l][sum - 1][i] % mod;
            ntt(g, -1);
            int j = (k * pw + l) % p;
            for (int i = 0; i <= m; ++i)
                f[j][sum][i] = (f[j][sum][i] + g[i]) % mod;
        }
    pw = pw * pw % p;
    if (k % 2 == 1)
    {
        ++sum;
        for (int i = 0; i <= 9; ++i)
            for (int j = 0; j <= m - i; ++j)
                for (int k = 0; k < p; ++k)
                {
                    int l = (i * pw + k) % p;
                    f[l][sum][j + i] = (f[l][sum][j + i] + f[k][sum - 1][j]) % mod;
                }
        pw = pw * 10 % p;
    }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &p, &m);
    while (num <= 2 * m)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
    dfs(n);
    for (int i = 0; i <= m; ++i)
    {
        ans = (ans + f[0][sum][i]) % mod;
        printf("%d ", ans);
    }
    return 0;
}