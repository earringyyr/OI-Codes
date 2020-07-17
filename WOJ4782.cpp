#include <iostream>
#include <cstdio>
#define mod 998244353
using namespace std;
int n, m, f[305][305], ans[305][305], p[305][305], g[10][305][305];
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (long long)b * a % mod;
        a = (long long)a * a % mod;
        k >>= 1;
    }
    return b;
}
void dfs(int l, int k)
{
    ans[l][k] = f[k][0];
    for (int i = 1; i <= n; ++i)
        if (i != k && f[k][i])
        {
            if (!p[l][i])
                dfs(l, i);
            ans[l][k] = (ans[l][k] - (long long)f[k][i] * ans[l][i]) % mod;
        }
    p[l][k] = 1;
    return;
}
void solve(int l, int r, int num)
{
    if (l == r)
    {
        p[l][r] = 1;
        for (int i = 1; i <= n; ++i)
            if (!p[l][i])
                dfs(l, i);
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = l; i <= r; ++i)
    {
        g[num][i][0] = f[i][0];
        for (int j = l; j <= r; ++j)
            g[num][i][j] = f[i][j];
    }
    for (int i = l; i <= mid; ++i)
    {
        int k = ksm(f[i][i], mod - 2);
        f[i][0] = (long long)f[i][0] * k % mod;
        for (int j = i; j <= r; ++j)
            f[i][j] = (long long)f[i][j] * k % mod;
        for (int j = i + 1; j <= r; ++j)
            if (f[j][i])
            {
                f[j][0] = (f[j][0] - (long long)f[i][0] * f[j][i]) % mod;
                for (int k = r; k >= i; --k)
                    f[j][k] = (f[j][k] - (long long)f[i][k] * f[j][i]) % mod;
            }
    }
    solve(mid + 1, r, num + 1);
    for (int i = l; i <= r; ++i)
    {
        f[i][0] = g[num][i][0];
        for (int j = l; j <= r; ++j)
            f[i][j] = g[num][i][j];
    }
    for (int i = r; i > mid; --i)
    {
        int k = ksm(f[i][i], mod - 2);
        f[i][0] = (long long)f[i][0] * k % mod;
        for (int j = l; j <= i; ++j)
            f[i][j] = (long long)f[i][j] * k % mod;
        for (int j = i - 1; j >= l; --j)
            if (f[j][i])
            {
                f[j][0] = (f[j][0] - (long long)f[i][0] * f[j][i]) % mod;
                for (int k = l; k <= i; ++k)
                    f[j][k] = (f[j][k] - (long long)f[i][k] * f[j][i]) % mod;
            }
    }
    solve(l, mid, num + 1);
    for (int i = l; i <= r; ++i)
    {
        f[i][0] = g[num][i][0];
        for (int j = l; j <= r; ++j)
            f[i][j] = g[num][i][j];
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ++f[u][u];
        ++f[u][0];
        --f[u][v];
    }
    solve(1, n, 0);
    for (int i = 2; i <= n; ++i)
        printf("%d\n", (ans[i][1] + mod) % mod);
    return 0;
}