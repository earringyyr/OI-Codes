#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, s, v, sum, ans, mch[105], vis[105], head[105];
double x[105], y[105], xx[105], yy[105];
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
bool dfs(int k, int t)
{
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v] != t)
        {
            vis[a[d].v] = t;
            if (!mch[a[d].v] || dfs(mch[a[d].v], t))
            {
                mch[a[d].v] = k;
                return true;
            }
        }
        d = a[d].nxt;
    }
    return false;
}
int main()
{
    while (scanf("%d%d%d%d", &n, &m, &s, &v) == 4)
    {
        ans = 0;
        sum = 0;
        memset(mch, 0, sizeof(mch));
        memset(vis, 0, sizeof(vis));
        memset(head, 0, sizeof(head));
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf", &x[i], &y[i]);
        for (int i = 1; i <= m; ++i)
            scanf("%lf%lf", &xx[i], &yy[i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if ((x[i] - xx[j]) * (x[i] - xx[j]) + (y[i] - yy[j]) * (y[i] - yy[j]) <= s * v * s * v)
                    ins(i, j);
        for (int i = 1; i <= n; ++i)
            if (dfs(i, i))
                ++ans;
        printf("%d\n", n - ans);
    }
    return 0;
}