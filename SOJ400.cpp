#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, top, col, cnt, tot, ans, head[10005], low[10005], dfn[10005], s[10005], co[10005], x[50005], y[50005], gu[10005], num[10005];
struct node
{
    int v;
    int next;
} a[50005];
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
            ++num[col];
            co[s[top]] = col;
            --top;
        }
        ++num[col];
        co[s[top]] = col;
        --top;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
        ins(x[i], y[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= m; ++i)
        if (co[x[i]] != co[y[i]])
            ++gu[co[x[i]]];
    for (int i = 1; i <= col; ++i)
        if (!gu[i])
        {
            ++tot;
            ans = num[i];
        }
    if (tot == 1)
        printf("%d", ans);
    else
        printf("%d", 0);
    return 0;
}