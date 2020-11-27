#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1000003;
typedef long long ll;
int n, k, m, q, sum;
int head[3005], fa[3005], dep[3005];
int lca[3005][3005], anc[3005][3005];
int f[6005][6005];
struct node
{
    int v;
    int nxt;
} a[3005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
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
int dist(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[lca[u][v]];
}
int main()
{
    scanf("%d%d%d%d", &n, &k, &m, &q);
    for (int i = 2; i <= n; ++i)
    {
        int u, v = i;
        scanf("%d", &u);
        dep[v] = dep[u] + 1;
        fa[v] = u;
        ins(u, v);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (i == j)
                lca[i][j] = i;
            else if (dep[i] < dep[j])
                lca[i][j] = lca[i][fa[j]];
            else
                lca[i][j] = lca[fa[i]][j];
        }
    anc[1][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        anc[i][0] = i;
        for (int j = 1; j <= n; ++j)
            anc[i][j] = anc[fa[i]][j - 1];
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v, a;
        scanf("%d%d%d", &u, &v, &a);
        if (dep[u] < dep[v])
            swap(u, v);
        int dis = dist(u, v);
        if (dis % 2 == 0)
            f[anc[u][dis / 2]][dis] = (f[anc[u][dis / 2]][dis] + a) % mod;
        else
            f[anc[u][dis / 2] + n - 1][dis] = (f[anc[u][dis / 2] + n - 1][dis] + a) % mod;
    }
    for (int i = n; i >= 1; --i)
    {
        int d = head[i];
        while (d)
        {
            for (int j = 0; j <= 2 * n - 2; j += 2)
                f[i][j] = (f[i][j] + f[a[d].v + n - 1][j + 1]) % mod;
            d = a[d].nxt;
        }
        if (i > 1)
        {
            for (int j = 1; j <= 2 * n - 2; j += 2)
                f[i + n - 1][j] = (f[i + n - 1][j] + f[i][j + 1]) % mod;
        }
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= 2 * n - 2; j += 2)
            f[i + n - 1][j] = (f[i + n - 1][j] + f[fa[i]][j + 1] - f[i + n - 1][j + 2] + mod) % mod;
        for (int j = 0; j <= 2 * n - 2; j += 2)
            f[i][j] = (f[i][j] + f[i + n - 1][j + 1] - f[i][j + 2] + mod) % mod;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 2 * n - 2; j >= 0; j -= 2)
            f[i][j] = (f[i][j] + f[i][j + 2]) % mod;
    for (int i = n + 1; i < 2 * n; ++i)
        for (int j = 2 * n - 3; j >= 1; j -= 2)
            f[i][j] = (f[i][j] + f[i][j + 2]) % mod;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= 2 * n - 2; j += 2)
            f[i][j] = ksm(f[i][j], k);
    for (int i = n + 1; i < 2 * n; ++i)
        for (int j = 1; j <= 2 * n - 2; j += 2)
            f[i][j] = ksm(f[i][j], k);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= 2 * n - 2; j += 2)
            f[i][j] = (f[i][j] - f[i][j + 2] + mod) % mod;
    for (int i = n + 1; i < 2 * n; ++i)
        for (int j = 1; j <= 2 * n - 2; j += 2)
            f[i][j] = (f[i][j] - f[i][j + 2] + mod) % mod;
    for (int i = n; i >= 2; --i)
    {
        for (int j = 2 * n - 2; j >= 0; j -= 2)
            f[i][j] = (f[i][j] - f[i + n - 1][j + 1] + f[i][j + 2] + mod) % mod;
        for (int j = 2 * n - 3; j >= 1; j -= 2)
            f[i + n - 1][j] = (f[i + n - 1][j] - f[fa[i]][j + 1] + f[i + n - 1][j + 2] + mod) % mod;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (i > 1)
        {
            for (int j = 2 * n - 3; j >= 1; j -= 2)
                f[i + n - 1][j] = (f[i + n - 1][j] - f[i][j + 1] + mod) % mod;
        }
        int d = head[i];
        while (d)
        {
            for (int j = 2 * n - 2; j >= 0; j -= 2)
                f[i][j] = (f[i][j] - f[a[d].v + n - 1][j + 1] + mod) % mod;
            d = a[d].nxt;
        }
    }
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (dep[u] < dep[v])
            swap(u, v);
        int dis = dist(u, v);
        if (dis % 2 == 0)
            printf("%d\n", f[anc[u][dis / 2]][dis]);
        else
            printf("%d\n", f[anc[u][dis / 2] + n - 1][dis]);
    }
    return 0;
}