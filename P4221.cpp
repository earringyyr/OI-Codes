#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, p, num;
int w[25], tot[25], fa[25];
int u[255], v[255];
int G[5000005], siz[5000005];
int f[25][5000005], g[25][5000005];
int lowbit(int x)
{
    return x & -x;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
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
void fwt(int *c, int type)
{
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = c[j + mid + k];
                c[j + k] = x;
                if (type == 1)
                    c[j + mid + k] = (x + y) % mod;
                else
                    c[j + mid + k] = (y - x + mod) % mod;
            }
    return;
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    num = 1 << n;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &u[i], &v[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int s = 1; s < num; ++s)
    {
        siz[s] = siz[s - lowbit(s)] + 1;
        memset(tot, 0, sizeof(tot));
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        for (int i = 1; i <= m; ++i)
            if ((s & (1 << (u[i] - 1))) && (s & (1 << (v[i] - 1))))
            {
                ++tot[u[i]];
                ++tot[v[i]];
                if (getfather(u[i]) != getfather(v[i]))
                    fa[getfather(u[i])] = getfather(v[i]);
            }
        int pp = 0, cnt = 0, ppp = 0;
        for (int i = 1; i <= n; ++i)
            if (s & (1 << (i - 1)))
            {
                if (tot[i] % 2 == 1)
                    pp = 1;
                cnt += w[i];
                if (getfather(i) == i)
                    ++ppp;
            }
        if (ppp > 1 || pp)
            g[siz[s]][s] = ksm(cnt, p);
        G[s] = ksm(cnt, p);
    }
    for (int i = 1; i <= n; ++i)
        fwt(g[i], 1);
    f[0][0] = 1;
    fwt(f[0], 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
            for (int k = 0; k < num; ++k)
                f[i][k] = (f[i][k] + (ll)f[j][k] * g[i - j][k] % mod) % mod;
        fwt(f[i], -1);
        for (int j = 0; j < num; ++j)
            if (siz[j] != i)
                f[i][j] = 0;
            else
                f[i][j] = (ll)f[i][j] * ksm(G[j], mod - 2) % mod;
        if (i != n)
            fwt(f[i], 1);
    }
    printf("%d", f[n][(1 << n) - 1]);
    return 0;
}