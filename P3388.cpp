#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, cnt, num, ans, head[20005], low[20005], dfn[20005], vis[20005];
struct node
{
    int v;
    int next;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k, int root)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v, root);
            low[k] = min(low[k], low[a[d].v]);
            if (low[a[d].v] >= dfn[k] && k != root)
            {
                if (!vis[k])
                    ++ans;
                vis[k] = 1;
            }
            if (k == root)
                ++num;
        }
        else
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].next;
    }
    if (k == root && num >= 2)
    {
        ++ans;
        vis[k] = 1;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
        {
            num = 0;
            tarjan(i, i);
        }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
        if (vis[i])
            printf("%d ", i);
    return 0;
}