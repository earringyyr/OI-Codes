#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, sum;
int head[200005], vis[200005], co[200005];
struct edge
{
    int v;
    int nxt;
} a[400005];
struct node
{
    int id;
    int x;
    int y;
} p[200005];
bool cmp1(node aa, node bb)
{
    return aa.x < bb.x;
}
bool cmp2(node aa, node bb)
{
    return aa.y < bb.y;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        if (!vis[a[d].v])
        {
            vis[a[d].v] = 1;
            co[a[d].v] = co[k] ^ 1;
            dfs(a[d].v);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        p[i].id = i;
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    sort(p + 1, p + n + 1, cmp1);
    for (int i = 2; i <= n; ++i)
        if (p[i].x == p[i - 1].x)
        {
            ins(p[i].id, p[i - 1].id);
            ins(p[i - 1].id, p[i].id);
            ++i;
        }
    sort(p + 1, p + n + 1, cmp2);
    for (int i = 2; i <= n; ++i)
        if (p[i].y == p[i - 1].y)
        {
            ins(p[i].id, p[i - 1].id);
            ins(p[i - 1].id, p[i].id);
            ++i;
        }
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i);
    for (int i = 1; i <= n; ++i)
        if (co[i] == 0)
            putchar('b');
        else
            putchar('r');
    return 0;
}