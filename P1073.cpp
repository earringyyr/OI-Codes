#include <iostream>
#include <cstdio>
#include <cstring>
#define inf 0x7f7f7f7f
using namespace std;
int n, m, sum, head[100005], w[100005], ma[100005], mi[100005];
struct node
{
    int v;
    int nxt;
} a[1000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int minx, int pre)
{
    bool p = true;
    minx = min(minx, w[k]);
    if (mi[k] > minx)
    {
        mi[k] = minx;
        p = false;
    }
    int maxn = max(ma[pre], w[k] - minx);
    if (ma[k] < maxn)
    {
        ma[k] = maxn;
        p = false;
    }
    if (p)
        return;
    int d = head[k];
    while (d)
    {
        dfs(a[d].v, minx, k);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    memset(mi, 0x7f, sizeof(mi));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (z == 1)
            ins(x, y);
        else
        {
            ins(x, y);
            ins(y, x);
        }
    }
    dfs(1, inf, 0);
    printf("%d", ma[n]);
    return 0;
}