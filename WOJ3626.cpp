#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum;
int head[2005];
bool vis[2005];
char ans[1005];
struct node
{
    int v;
    int next;
} a[8005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
void dfs(int x)
{
    vis[x] = 1;
    int d = head[x];
    while (d)
    {
        if (!vis[a[d].v])
            dfs(a[d].v);
        d = a[d].next;
    }
    return;
}
bool check(int x)
{
    memset(vis, 0, sizeof(vis));
    dfs(x);
    for (int i = 1; i <= n; ++i)
        if (vis[i] && vis[i + n])
            return false;
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int k = 1; k <= m; ++k)
    {
        int i, a, j, b;
        char aa, bb;
        scanf("%d %c%d %c", &i, &aa, &j, &bb);
        if (aa == 'Y')
            a = 1;
        else
            a = 0;
        if (bb == 'Y')
            b = 1;
        else
            b = 0;
        if (a && b)
        {
            ins(i + n, j);
            ins(j + n, i);
        }
        if (a && !b)
        {
            ins(i + n, j + n);
            ins(j, i);
        }
        if (!a && b)
        {
            ins(i, j);
            ins(j + n, i + n);
        }
        if (!a && !b)
        {
            ins(i, j + n);
            ins(j, i + n);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        bool p1 = check(i), p2 = check(i + n);
        if (!p1 && !p2)
        {
            puts("IMPOSSIBLE");
            return 0;
        }
        else if (p1 && p2)
            ans[i] = '?';
        else if (p1)
            ans[i] = 'Y';
        else if (p2)
            ans[i] = 'N';
    }
    for (int i = 1; i <= n; ++i)
        putchar(ans[i]);
    return 0;
}