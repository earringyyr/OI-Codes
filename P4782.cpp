#include <iostream>
#include <cstdio>
using namespace std;
int n, m, sum, cnt, top, col;
int head[2000005], s[2000005];
int low[2000005], dfn[2000005];
int co[2000005], num[2000005];
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
        while (dfn[s[top]] != low[s[top]])
        {
            co[s[top]] = col;
            --top;
        }
        co[s[top]] = col;
        top--;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int k = 1; k <= m; ++k)
    {
        int i, a, j, b;
        scanf("%d%d%d%d", &i, &a, &j, &b);
        if (a && b)
        {
            num[i + n]++;
            num[j + n]++;
            ins(i + n, j);
            ins(j + n, i);
        }
        if (a && !b)
        {
            num[j + n]++;
            num[j]++;
            ins(i + n, j + n);
            ins(j, i);
        }
        if (!a && b)
        {
            num[i]++;
            num[j + n]++;
            ins(i, j);
            ins(j + n, i + n);
        }
        if (!a && !b)
        {
            num[i]++;
            num[j]++;
            ins(i, j + n);
            ins(j, i + n);
        }
    }
    for (int i = 1; i <= 2 * n; ++i)
        if (!dfn[i])
            tarjan(i);
    bool p = true;
    for (int i = 1; i <= n; ++i)
        if (co[i] == co[i + n])
        {
            p = false;
            break;
        }
    if (!p)
        printf("IMPOSSIBLE");
    else
    {
        printf("POSSIBLE\n");
        for (int i = 1; i <= n; ++i)
            if (co[i] < co[i + n])
                cout << 1 << " ";
            else
                cout << 0 << " ";
    }
    return 0;
}