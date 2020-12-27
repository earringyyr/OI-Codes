#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, q, sum;
int p[200005], a[200005];
int pre[200005], lst[200005];
int head[200005], vis[200005], maxn[200005];
int cnt, l[200005];
int ans[200005];
struct node
{
    int v;
    int nxt;
} e[200005];
void ins(int u, int v)
{
    ++sum;
    e[sum].v = v;
    e[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    vis[k] = 1;
    l[++cnt] = k;
    if (cnt >= n)
        maxn[k] = max(maxn[k], l[cnt - n + 1]);
    int d = head[k];
    while (d)
    {
        dfs(e[d].v);
        d = e[d].nxt;
    }
    --cnt;
}
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        pre[p[i]] = p[i - 1];
    }
    pre[p[1]] = p[n];
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &a[i]);
        if (lst[pre[a[i]]])
            ins(lst[pre[a[i]]], i);
        lst[a[i]] = i;
    }
    for (int i = 1; i <= m; ++i)
        if (!vis[i])
            dfs(i);
    for (int i = 1; i <= m; ++i)
        maxn[i] = max(maxn[i], maxn[i - 1]);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l <= maxn[r])
            putchar('1');
        else
            putchar('0');
    }
    return 0;
}