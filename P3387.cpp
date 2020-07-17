#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int cnt, sum, col, top, ans;
int vis[1005], f[10005];
int w[10005], du[10005];
int uu[100005], vv[100005];
int head[10005], st[10005];
int dfn[10005], low[10005];
int co[10005], num[10005];
struct node
{
    int v;
    int next;
} a[100005];
void build(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void tarjan(int k)
{
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    st[++top] = k;
    int d = head[k];
    while (d != 0)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
        }
        else if (!co[a[d].v])
            low[k] = min(low[k], low[a[d].v]);
        d = a[d].next;
    }
    if (dfn[k] == low[k])
    {
        col++;
        while (dfn[st[top]] != low[st[top]])
        {
            num[col] += w[st[top]];
            co[st[top]] = col;
            top--;
        }
        co[st[top]] = col;
        num[col] += w[st[top]];
        top--;
    }
    return;
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i <= m; ++i)
    {
        cin >> uu[i] >> vv[i];
        build(uu[i], vv[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    sum = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i)
        if (co[uu[i]] != co[vv[i]])
        {
            build(co[uu[i]], co[vv[i]]);
            du[co[vv[i]]]++;
        }
    top = 0;
    for (int i = 1; i <= col; ++i)
        if (!du[i])
        {
            st[++top] = i;
            f[i] = num[i];
            ans = max(ans, f[i]);
        }
    for (int i = 1; i <= col; ++i)
    {
        int d = head[st[i]];
        memset(vis, 0, sizeof(vis));
        while (d)
        {
            f[a[d].v] = max(f[st[i]] + num[a[d].v], f[a[d].v]);
            ans = max(ans, f[a[d].v]);
            du[a[d].v]--;
            if (!du[a[d].v])
                st[++top] = a[d].v;
            d = a[d].next;
        }
    }
    cout << ans;
    return 0;
}