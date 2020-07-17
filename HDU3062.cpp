#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum, cnt, col, top;
int head[2005], dfn[2005];
int co[2005], low[2005];
int s[2005];
struct node
{
    int v;
    int next;
} a[2000005];
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
            low[k] = min(low[k], low[a[d].v]);
        d = a[d].next;
    }
    if (low[k] == dfn[k])
    {
        col++;
        while (low[s[top]] != dfn[s[top]])
        {
            co[s[top]] = col;
            top--;
        }
        co[s[top]] = col;
        top--;
    }
    return;
}
int main()
{
    while (cin >> n >> m)
    {
        sum = 0;
        cnt = 0;
        col = 0;
        top = 0;
        memset(head, 0, sizeof(head));
        memset(dfn, 0, sizeof(dfn));
        memset(co, 0, sizeof(co));
        for (int k = 1; k <= m; ++k)
        {
            int i, j, a, b;
            scanf("%d%d%d%d", &i, &j, &a, &b);
            if (a && b)
            {
                ins(i, j + n);
                ins(j, i + n);
            }
            if (a && !b)
            {
                ins(i, j);
                ins(j + n, i + n);
            }
            if (!a && b)
            {
                ins(i + n, j + n);
                ins(j, i);
            }
            if (!a && !b)
            {
                ins(i + n, j);
                ins(j + n, i);
            }
        }
        for (int i = 0; i < 2 * n; ++i)
            if (!dfn[i])
                tarjan(i);
        bool p = true;
        for (int i = 0; i < n; ++i)
            if (co[i] == co[i + n])
            {
                p = false;
                break;
            }
        if (p)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}