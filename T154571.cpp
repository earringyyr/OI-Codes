#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, m, K, S, lg, tot, ans;
int f[2005][55];
int fac[200005], inv[200005];
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
} a[2005];
bool cmp(node aa, node bb)
{
    return aa.x + aa.y < bb.x + bb.y;
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
int C(int n, int m)
{
    if (n < m)
        return 0;
    return (ll)fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int ways(int x, int y)
{
    if (a[x].x > a[y].x || a[x].y > a[y].y)
        return 0;
    return C(a[y].x + a[y].y - a[x].x - a[x].y, a[y].x - a[x].x);
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &K, &S);
    for (int i = 1; i <= K; ++i)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        --a[i].x;
        --a[i].y;
    }
    a[K + 1].x = 0;
    a[K + 1].y = 0;
    a[K + 2].x = n - 1;
    a[K + 2].y = m - 1;
    K += 2;
    sort(a + 1, a + K + 1, cmp);
    fac[0] = 1;
    for (int i = 1; i <= n + m; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    inv[n + m] = ksm(fac[n + m], mod - 2);
    for (int i = n + m - 1; i >= 0; --i)
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    int SS = S;
    while (SS > 1)
    {
        SS = (SS + 1) / 2;
        ++lg;
    }
    lg += 2;
    for (int i = 1; i <= K; ++i)
        for (int j = 1; j <= lg; ++j)
        {
            f[i][j] = C(a[i].x + a[i].y, a[i].x);
            if (j != lg)
                for (int k = 1; k < i; ++k)
                    f[i][j] = (f[i][j] - (ll)f[k][j] * ways(k, i) % mod + mod) % mod;
            for (int k = 1; k < j; ++k)
                f[i][j] = (f[i][j] - f[i][k] + mod) % mod;
        }
    for (int i = 2; i <= lg; ++i)
        tot = (tot + f[K][i]) % mod;
    for (int i = 2; i <= lg; ++i)
    {
        ans = (ans + (ll)S * f[K][i] % mod * ksm(tot, mod - 2) % mod) % mod;
        S = (S + 1) / 2;
    }
    printf("%d", ans);
    return 0;
}