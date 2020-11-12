#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, sum, cnt;
int head[5005];
int num[5005][5005];
ll g[2][5][2];
ll f[5][5005];
ll ans;
struct node
{
    int v;
    int nxt;
} a[10005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa, int dep)
{
    ++num[cnt][dep];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs(a[d].v, k, dep + 1);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
    {
        cnt = 0;
        int d = head[i];
        while (d)
        {
            ++cnt;
            dfs(a[d].v, i, 1);
            d = a[d].nxt;
        }
        memset(f, 0, sizeof(f));
        for (int j = 1; j <= cnt; ++j)
        {
            ll cal = 0, tot[3] = {1, 0, 0};
            for (int k = 1; k <= n; ++k)
            {
                tot[1] = tot[1] + f[1][k];
                tot[2] = tot[2] + f[2][k];
                f[3][k] += tot[2] * num[j][k] + f[2][k] * cal;
                f[2][k] += tot[1] * num[j][k] + f[1][k] * cal;
                f[1][k] += tot[0] * num[j][k];
                cal += num[j][k];
            }
        }
        for (int j = 1; j <= n; ++j)
            ans -= f[3][j] * j;
        memset(g, 0, sizeof(g));
        g[0][0][0] = 1;
        g[1][0][0] = 1;
        for (int j = 1; j <= cnt; ++j)
        {
            g[1][1][0] = g[0][1][0];
            g[1][2][0] = g[0][2][0];
            g[1][3][0] = g[0][3][0];
            g[1][1][1] = g[0][1][1];
            g[1][2][1] = g[0][2][1];
            g[1][3][1] = g[0][3][1];
            for (int k = 1; k <= n; ++k)
            {
                g[1][1][0] += g[0][0][0] * num[j][k];
                g[1][2][0] += g[0][1][0] * num[j][k];
                g[1][3][0] += g[0][2][0] * num[j][k];
                g[1][1][1] += g[0][0][1] * num[j][k] + g[0][0][0] * num[j][k] * k;
                g[1][2][1] += g[0][1][1] * num[j][k] + g[0][1][0] * num[j][k] * k;
                g[1][3][1] += g[0][2][1] * num[j][k] + g[0][2][0] * num[j][k] * k;
            }
            swap(g[0], g[1]);
        }
        ans += g[0][3][1];
        memset(f, 0, sizeof(f));
        for (int j = 1; j <= cnt; ++j)
        {
            ll cal = 0, tot[2] = {1, 0};
            for (int k = n; k >= 1; --k)
            {
                tot[1] = tot[1] + f[1][k];
                f[2][k] += tot[1] * num[j][k] + f[1][k] * cal;
                f[1][k] += tot[0] * num[j][k];
                cal += num[j][k];
            }
        }
        for (int j = 1; j <= n; ++j)
            ans += f[2][j] * j;
        for (int j = 1; j <= cnt; ++j)
            for (int k = 1; k <= n; ++k)
                num[j][k] = 0;
    }
    printf("%lld", ans);
    return 0;
}