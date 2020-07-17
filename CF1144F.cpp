#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, sum, head[200005], vis[200005];
struct node
{
    int v;
    int next;
} a[400005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k)
{
    int d = head[k];
    while (d)
    {
        if (vis[k] == vis[a[d].v])
            return false;
        if (vis[a[d].v] == -1)
        {
            vis[a[d].v] = vis[k] ^ 1;
            if (!dfs(a[d].v))
                return false;
        }
        d = a[d].next;
    }
    return true;
}
int main()
{
    memset(vis, -1, sizeof(vis));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    vis[1] = 1;
    if (dfs(1))
    {
        puts("YES");
        for (int i = 1; i <= 2 * m; i += 2)
            putchar(vis[a[i].v] + 48);
    }
    else
        puts("NO");
    return 0;
}