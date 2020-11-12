#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, top, sum = 1, cnt;
int num[100005], st[100005], head[100005], vis[500005];
struct node
{
    int v;
    int nxt;
} a[500005];
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
    while (head[k])
    {
        int d = head[k];
        head[k] = a[d].nxt;
        if (vis[d])
            continue;
        vis[d] = 1;
        vis[d ^ 1] = 1;
        dfs(a[d].v);
        ++cnt;
        if (cnt & 1)
            printf("%d %d\n", k, a[d].v);
        else
            printf("%d %d\n", a[d].v, k);
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
        ++num[u];
        ++num[v];
    }
    for (int i = 1; i <= n; ++i)
        if (num[i] & 1)
            st[++top] = i;
    for (int i = 1; i <= top; i += 2)
    {
        ins(st[i], st[i + 1]);
        ins(st[i + 1], st[i]);
        ++m;
    }
    if (m & 1)
    {
        ins(1, 1);
        ++m;
    }
    printf("%d\n", m);
    dfs(1);
    return 0;
}