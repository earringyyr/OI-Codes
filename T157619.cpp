#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, sum, ans = 1;
int head[200005], v[200005], vis[200005];
long double f[200005][2];
struct node
{
    int v;
    int nxt;
} a[400005];
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
    f[k][0] = 1;
    f[k][1] = v[k];
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            if (f[a[d].v][1] > f[a[d].v][0])
            {
                f[k][0] *= f[a[d].v][1];
                f[k][1] *= f[a[d].v][0];
            }
        }
        d = a[d].nxt;
    }
    return;
}
void dfs2(int k, int fa)
{
    if (vis[k])
        ans = (ll)ans * v[k] % mod;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            if (vis[k])
                vis[a[d].v] = 0;
            else
            {
                if (f[a[d].v][0] < f[a[d].v][1])
                    vis[a[d].v] = 1;
                else
                    vis[a[d].v] = 0;
            }
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &v[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    if (f[1][0] < f[1][1])
        vis[1] = 1;
    dfs2(1, 0);
    printf("%d", ans);
    return 0;
}