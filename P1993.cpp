#include <iostream>
#include <cstdio>
#define inf -1000000000
using namespace std;
int n, m, sum, head[10005], s[10005], vis[10005];
struct node
{
    int v;
    int w;
    int next;
} a[30005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].next = head[u];
    head[u] = sum;
    return;
}
bool spfa(int k)
{
    vis[k] = 1;
    int d = head[k];
    while (d)
    {
        if (s[a[d].v] < s[k] + a[d].w)
        {
            s[a[d].v] = s[k] + a[d].w;
            if (vis[a[d].v])
                return false;
            if (!spfa(a[d].v))
                return false;
        }
        d = a[d].next;
    }
    vis[k] = 0;
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int type, a, b, c;
        scanf("%d", &type);
        if (type == 1)
        {
            scanf("%d%d%d", &a, &b, &c);
            ins(b, a, c);
        }
        if (type == 2)
        {
            scanf("%d%d%d", &a, &b, &c);
            ins(a, b, -c);
        }
        if (type == 3)
        {
            scanf("%d%d", &a, &b);
            ins(a, b, 0);
            ins(b, a, 0);
        }
    }
    for (int i = 1; i <= n; ++i)
        ins(0, i, 0);
    for (int i = 1; i <= n; ++i)
        s[i] = inf;
    if (spfa(0))
        printf("Yes");
    else
        printf("No");
    return 0;
}