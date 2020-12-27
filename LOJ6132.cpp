#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int p = 1000000007;
const int mod1 = 469762049, mod2 = 998244353, mod3 = 1004535809;
int N, M, P, v, L1, L2;
int mod, num = 1, ans;
int f[2];
int c[105];
int inv[10005];
int val[20005], dp[20005];
int r[40005], gg[40005];
int g[5][40005];
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
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
void ntt1(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod1 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod1 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod1;
                c[j + k] = (x + y) % mod1;
                c[j + mid + k] = (x - y + mod1) % mod1;
                ww = (ll)w * ww % mod1;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod1 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod1;
    }
    return;
}
void ntt2(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod2 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod2 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod2;
                c[j + k] = (x + y) % mod2;
                c[j + mid + k] = (x - y + mod2) % mod2;
                ww = (ll)w * ww % mod2;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod2 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod2;
    }
    return;
}
void ntt3(int *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        int w = ksm(3, (mod3 - 1) / (mid << 1));
        if (type == -1)
            w = ksm(w, mod3 - 2);
        for (int j = 0; j < num; j += (mid << 1))
        {
            int ww = 1;
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = (ll)ww * c[j + mid + k] % mod3;
                c[j + k] = (x + y) % mod3;
                c[j + mid + k] = (x - y + mod3) % mod3;
                ww = (ll)w * ww % mod3;
            }
        }
    }
    if (type == -1)
    {
        int inv = ksm(num, mod3 - 2);
        for (int i = 0; i < num; ++i)
            c[i] = (ll)c[i] * inv % mod3;
    }
    return;
}
int main()
{
    mod = p;
    for (int i = 0; i <= 10000; ++i)
        inv[i] = ksm(i, mod - 2);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        memset(g, 0, sizeof(g));
        memset(dp, 0, sizeof(dp));
        scanf("%d%d%d", &N, &M, &P);
        for (int i = 1; i <= M; ++i)
        {
            scanf("%d", &c[i]);
            if (i == 1)
                v = c[i];
            else
                v = gcd(v, c[i]);
        }
        sort(c + 1, c + M + 1);
        g[0][0] = 1;
        g[1][0] = g[0][0];
        g[2][0] = g[0][0];
        g[3][0] = g[0][0];
        L1 = 0;
        if (v == 1)
        {
            f[0] = 100;
            f[1] = 0;
            L2 = 0;
        }
        else
        {
            f[0] = 100 - P;
            f[1] = P;
            L2 = 1;
        }
        int k = N, len = 0;
        while ((1 << (len + 1)) <= k)
            ++len;
        while (len >= 0)
        {
            num = 1;
            while (num < 2 * (L1 + 1) - 1)
                num <<= 1;
            for (int i = 0; i < num; ++i)
                r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (num >> 1) : 0);
            mod = mod1;
            ntt1(g[1], 1);
            for (int i = 0; i < num; ++i)
                g[1][i] = (ll)g[1][i] * g[1][i] % mod;
            ntt1(g[1], -1);
            mod = mod2;
            ntt2(g[2], 1);
            for (int i = 0; i < num; ++i)
                g[2][i] = (ll)g[2][i] * g[2][i] % mod;
            ntt2(g[2], -1);
            mod = mod3;
            ntt3(g[3], 1);
            for (int i = 0; i < num; ++i)
                g[3][i] = (ll)g[3][i] * g[3][i] % mod;
            ntt3(g[3], -1);
            mod = mod2;
            int inv1 = ksm(mod1, mod2 - 2);
            mod = mod3;
            int inv2 = ksm((ll)mod1 * mod2 % mod3, mod3 - 2);
            mod = p;
            for (int i = 0; i < num; ++i)
            {
                ll tmp = (ll)(g[2][i] - g[1][i] + mod2) % mod2 * inv1 % mod2 * mod1 + g[1][i];
                tmp = ((ll)((g[3][i] - tmp) % mod3 + mod3) % mod3 * inv2 % mod3 * mod1 % mod * mod2 % mod + tmp) % mod;
                g[0][i] = 0;
                g[0][i % v] = (g[0][i % v] + tmp) % mod;
            }
            L1 = 0;
            for (int i = 0; i < num; ++i)
            {
                g[1][i] = g[0][i] % mod1;
                g[2][i] = g[0][i] % mod2;
                g[3][i] = g[0][i] % mod3;
                if (g[0][i])
                    L1 = i;
            }
            if (k & (1 << len))
            {
                mod = p;
                memcpy(gg, g[0], sizeof(g[0]));
                memset(g[0], 0, sizeof(g[0]));
                for (int i = 0; i <= L1; ++i)
                    for (int j = 0; j <= L2; ++j)
                        g[0][(i + j) % v] = (g[0][(i + j) % v] + (ll)gg[i] * f[j] % mod) % mod;
                L1 = 0;
                for (int i = 0; i < v; ++i)
                {
                    g[1][i] = g[0][i] % mod1;
                    g[2][i] = g[0][i] % mod2;
                    g[3][i] = g[0][i] % mod3;
                    if (g[0][i])
                        L1 = i;
                }
            }
            --len;
        }
        mod = p;
        for (int i = 1; i < v; ++i)
            ans = (ans + (ll)g[0][i] * (v - i)) % mod;
        int pos = 1;
        int maxn = c[1] * c[M];
        if (M == 1)
            maxn = 0;
        dp[0] = 1;
        for (int i = 1; i <= maxn; ++i)
        {
            for (int j = 1; j <= M; ++j)
                if (i >= c[j] && dp[i - c[j]])
                {
                    dp[i] = 1;
                    break;
                }
            if (dp[i])
            {
                for (int j = pos; j <= i; ++j)
                    val[j] = i;
                pos = i + 1;
            }
        }
        int C = 1;
        for (int i = 1; i <= min(N, maxn); ++i)
        {
            C = (ll)C * (N - i + 1) % mod * inv[i] % mod;
            ans = (ans + (ll)(val[i] - v * ((i + v - 1) / v) + mod) * ksm(P, i) % mod * ksm(100 - P, N - i) % mod * C % mod) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}