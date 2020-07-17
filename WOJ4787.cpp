#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, cap, sum, num;
int b[400005], head[400005], cnt[400005][50];
long long ans[400005], f[400005];
struct node
{
    int v;
    int nxt;
} a[800005];
struct point
{
    int id;
    long long f;
} s[400005];
bool cmp(point aa, point bb)
{
    return aa.f < bb.f;
}
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
    int d = head[k];
    f[k] = b[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            f[k] += f[a[d].v];
        }
        d = a[d].nxt;
    }
    s[k].id = k;
    s[k].f = f[k];
    return;
}
void dfs2(int k, int fa)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs2(a[d].v, k);
            for (int i = 0; i < num; ++i)
                cnt[k][i] += cnt[a[d].v][i] + ((f[a[d].v] & (1 << i)) != 0);
        }
        d = a[d].nxt;
    }
    return;
}
void solve(int k)
{
    int x = 0, y = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i].f != s[i - 1].f)
        {
            x += y;
            y = 0;
        }
        ans[s[i].id] |= (1 << k) * (x > cnt[s[i].id][k]);
        y += ((s[i].f & (1 << k)) != 0);
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &cap);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    dfs1(cap, 0);
    sort(s + 1, s + n + 1, cmp);
    while (f[cap])
    {
        ++num;
        f[cap] >>= 1;
    }
    dfs2(cap, 0);
    for (int i = 0; i < num; ++i)
        solve(i);
    for (int i = 1; i <= n; ++i)
        printf("%lld ", ans[i]);
    return 0;
}