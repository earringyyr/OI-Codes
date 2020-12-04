#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, cnt, top, col;
int head[2000005], dfn[2000005], low[2000005], co[2000005], st[2000005];
struct node
{
    int v;
    int nxt;
} a[2000005];
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
    st[++top] = k;
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
        d = a[d].nxt;
    }
    if (dfn[k] == low[k])
    {
        ++col;
        while (dfn[st[top]] != low[st[top]])
        {
            co[st[top]] = col;
            --top;
        }
        co[st[top]] = col;
        --top;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &a, &y, &b);
        if (a == 0 && b == 0)
        {
            ins(x + n, y);
            ins(y + n, x);
        }
        if (a == 0 && b == 1)
        {
            ins(x + n, y + n);
            ins(y, x);
        }
        if (a == 1 && b == 0)
        {
            ins(x, y);
            ins(y + n, x + n);
        }
        if (a == 1 && b == 1)
        {
            ins(x, y + n);
            ins(y, x + n);
        }
    }
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (co[i] == co[i + n])
        {
            printf("IMPOSSIBLE");
            return 0;
        }
    puts("POSSIBLE");
    for (int i = 1; i <= n; ++i)
        if (co[i] < co[i + n])
            printf("0 ");
        else
            printf("1 ");
    return 0;
}