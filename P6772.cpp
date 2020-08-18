#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, T, k, sum, type = 1, c[55], head[55], dis[55];
ll ans, f[55][60005], vis[55][60005];
struct node
{
    int v;
    int w;
    int nxt;
} a[505];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &T, &k);
    if (n != m)
        type = 0;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(v, u, w);
        dis[v] = dis[u] + w;
        if (v != u % n + 1)
            type = 0;
    }
    if (type)
    {
        if (T % dis[1] != 0)
        {
            printf("-1");
            return 0;
        }
        for (int i = 1; i <= n; ++i)
            ans += c[i];
        ans *= T / dis[1];
        ans += c[1];
        for (int i = 1; i <= k; ++i)
        {
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            if (t % dis[1] == dis[x])
                ans += y;
        }
        printf("%lld", ans);
        return 0;
    }
    for (int i = 1; i <= k; ++i)
    {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        f[x][t] += y;
    }
    vis[1][0] = 1;
    f[1][0] = c[1];
    for (int i = 1; i <= T; ++i)
        for (int j = 1; j <= n; ++j)
        {
            ll tmp = f[j][i];
            f[j][i] = 0;
            int d = head[j];
            while (d)
            {
                if (i >= a[d].w && vis[a[d].v][i - a[d].w])
                {
                    vis[j][i] = 1;
                    f[j][i] = max(f[j][i], f[a[d].v][i - a[d].w] + c[j]);
                }
                d = a[d].nxt;
            }
            f[j][i] += tmp;
        }
    if (!vis[1][T])
        printf("-1");
    else
        printf("%lld", f[1][T]);
    return 0;
}