#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, k, sum;
int head[300005];
struct edge
{
    int v;
    int w;
    int val;
    int nxt;
} a[600005];
struct node
{
    int num;
    ll val;
    node(int aa = 0, ll bb = 0)
    {
        num = aa;
        val = bb;
    }
    bool operator<(const node &bb) const
    {
        if (val != bb.val)
            return val < bb.val;
        return num < bb.num;
    }
    node operator+(const node &bb) const
    {
        return node(num + bb.num, val + bb.val);
    }
} f[300005][3];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int fa, ll mid)
{
    f[k][0] = node(0, 0);
    f[k][1] = node(0, 0);
    f[k][2] = node(1, -mid);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs(a[d].v, k, mid);
            f[k][2] = max(f[k][2] + f[a[d].v][0], f[k][1] + f[a[d].v][1] + node(1, a[d].w - mid));
            f[k][1] = max(f[k][0] + f[a[d].v][1] + node(0, a[d].w), f[k][1] + f[a[d].v][0]);
            f[k][0] = f[k][0] + f[a[d].v][0];
        }
        d = a[d].nxt;
    }
    f[k][0] = max(max(f[k][0], f[k][1] + node(1, -mid)), f[k][2]);
    return;
}
bool check(ll mid)
{
    dfs(1, 0, mid);
    return f[1][0].num >= k + 1;
}
int main()
{
    ll lef = 0, rig = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
        if (w > 0)
            rig += w;
        else
            rig -= w;
    }
    lef = -rig;
    while (lef < rig)
    {
        ll mid = (lef + rig + 1) >> 1;
        if (check(mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    dfs(1, 0, lef);
    printf("%lld", f[1][0].val + lef * (k + 1));
    return 0;
}