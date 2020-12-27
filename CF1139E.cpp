#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, d, sum, t;
int p[5005], c[5005], k[5005], mch[5005];
int head[5005], vis[5005], ans[5005];
struct node
{
    int v;
    int nxt;
} a[5005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k, int tim)
{
    int d = head[k];
    while (d)
    {
        if (vis[a[d].v] != tim)
        {
            vis[a[d].v] = tim;
            if (!mch[a[d].v] || dfs(mch[a[d].v], tim))
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
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        ++p[i];
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i)
        vis[i] = 1;
    scanf("%d", &d);
    for (int i = 1; i <= d; ++i)
    {
        scanf("%d", &k[i]);
        vis[k[i]] = 0;
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 1)
            ins(p[i], c[i]);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= 5000; ++i)
        if (dfs(i, ++t))
            ++ans[d + 1];
        else
            break;
    for (int i = d; i >= 1; --i)
    {
        ans[i] = ans[i + 1];
        for (int j = ans[i + 1] + 1; j <= 5000; ++j)
            if (dfs(j, ++t))
                ++ans[i];
            else
                break;
        ins(p[k[i]], c[k[i]]);
    }
    for (int i = 1; i <= d; ++i)
        printf("%d\n", ans[i]);
    return 0;
}