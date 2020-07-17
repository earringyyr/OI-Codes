#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, t, sum, cnt, col, top, num;
int x[100005], y[100005], head[100005];
int s[100005], dfn[100005], low[100005];
int q[100005], co[100005], vis[100005];
struct node
{
    int v;
    int next;
} a[100005];
struct point
{
    int u;
    int v;
} b[100005];
bool cmp(point aa, point bb)
{
    return aa.u < bb.u;
}
void ins(int u, int v)
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
    s[++top] = k;
    int d = head[k];
    while (d)
    {
        if (!dfn[a[d].v])
        {
            tarjan(a[d].v);
            low[k] = min(low[k], low[a[d].v]);
        }
        else if (!co[a[d].v])
            low[k] = min(low[k], dfn[a[d].v]);
        d = a[d].next;
    }
    if (dfn[k] == low[k])
    {
        ++col;
        while (dfn[s[top]] != low[s[top]])
        {
            co[s[top]] = col;
            --top;
        }
        co[s[top]] = col;
        --top;
    }
    return;
}
void dfs(int k)
{
    q[++num] = k;
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
            dfs(a[d].v);
        d = a[d].next;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
        ins(x[i], y[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    sum = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i <= m; ++i)
        if (co[x[i]] != co[y[i]])
            ins(co[x[i]], co[y[i]]);
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d%d", &b[i].u, &b[i].v);
        b[i].u = co[b[i].u];
        b[i].v = co[b[i].v];
    }
    sort(b + 1, b + t + 1, cmp);
    for (int i = 1; i <= t; ++i)
    {
        if (b[i].u != b[i - 1].u)
        {
            for (int j = 1; j <= num; ++j)
                vis[q[j]] = 0;
            num = 0;
            dfs(b[i].u);
        }
        if (vis[b[i].v])
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES\n%d\n", m);
    for (int i = 1; i <= m; ++i)
        printf("%d %d\n", x[i], y[i]);
    return 0;
}