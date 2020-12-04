#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, cnt, rt, num, ans;
int head[20005], dfn[20005], low[20005], vis[20005];
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
            if (low[a[d].v] >= dfn[k] && k != rt)
            {
                if (!vis[k])
                    ++ans;
                vis[k] = 1;
            }
            if (k == rt)
                ++num;
        }
        else
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].nxt;
    }
    if (k == rt && num >= 2)
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
            cnt = 0;
            num = 0;
            rt = i;
            tarjan(i);
        }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
        if (vis[i])
            printf("%d ", i);
    return 0;
}