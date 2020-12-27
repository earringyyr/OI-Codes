#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, sum, rt;
int head[500005], siz[500005];
ll f[500005];
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
void dfs1(int k, int fa)
{
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    if (fa)
        f[k] = f[fa] + (ll)(siz[fa] - siz[k]) * siz[k];
    if (f[k] > f[rt])
        rt = k;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
            dfs2(a[d].v, k);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    f[rt] = 0;
    dfs1(rt, 0);
    dfs2(rt, 0);
    printf("%lld", f[rt] + (ll)n * (n - 1) / 2);
    return 0;
}