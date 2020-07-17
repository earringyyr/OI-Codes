#include <iostream>
#include <cstdio>
using namespace std;
int n, sum, cnt, col, top, ans, num, head[205], in[205], ou[205], dfn[205], low[205], co[205], s[205];
struct node
{
    int v;
    int next;
} a[40005];
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
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int v;
        while (scanf("%d", &v))
        {
            if (v == 0)
                break;
            ins(i, v);
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
    {
        int d = head[i];
        while (d)
        {
            if (co[i] != co[a[d].v])
            {
                ++in[co[a[d].v]];
                ++ou[co[i]];
            }
            d = a[d].next;
        }
    }
    for (int i = 1; i <= col; ++i)
    {
        if (!in[i])
            ++ans;
        if (!ou[i])
            ++num;
    }
    printf("%d", ans);
    return 0;
}