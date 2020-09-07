#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, sum, cnt, ans;
int head[50005], dfn[50005], low[50005];
int f[50005], fa[50005], dep[50005];
int st[100005], q[100005];
struct node
{
    int v;
    int nxt;
} a[20000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void solve(int u, int v)
{
    int k = v, top = dep[v] - dep[u] + 1;
    while (k != u)
    {
        st[top--] = f[k];
        k = fa[k];
    }
    st[top] = f[u];
    top = dep[v] - dep[u] + 1;
    for (int i = 1; i <= top; ++i)
        st[top + i] = st[i];
    int l = 1, r = 1;
    q[1] = 1;
    for (int i = 2; i <= top * 2; ++i)
    {
        while (l <= r && i - q[l] > top / 2)
            ++l;
        ans = max(ans, st[i] + i + st[q[l]] - q[l]);
        while (l <= r && st[q[r]] - q[r] < st[i] - i)
            --r;
        q[++r] = i;
    }
    for (int i = 2; i <= top; ++i)
        f[u] = max(f[u], st[i] + min(i - 1, top - i + 1));
    return;
}
void tarjan(int k, int Fa)
{
    fa[k] = Fa;
    ++cnt;
    dfn[k] = cnt;
    low[k] = cnt;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k])
        {
            if (!dfn[a[d].v])
            {
                dep[a[d].v] = dep[k] + 1;
                tarjan(a[d].v, k);
                low[k] = min(low[k], low[a[d].v]);
            }
            else
                low[k] = min(low[k], dfn[a[d].v]);
            if (low[a[d].v] > dfn[k])
            {
                ans = max(ans, f[k] + f[a[d].v] + 1);
                f[k] = max(f[k], f[a[d].v] + 1);
            }
        }
        d = a[d].nxt;
    }
    d = head[k];
    while (d)
    {
        if (fa[a[d].v] != k && dfn[k] < dfn[a[d].v])
            solve(k, a[d].v);
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int k;
        scanf("%d", &k);
        int u, v = 0;
        for (int i = 1; i <= k; ++i)
        {
            scanf("%d", &u);
            if (v)
            {
                ins(u, v);
                ins(v, u);
            }
            v = u;
        }
    }
    tarjan(1, 0);
    printf("%d", ans);
    return 0;
}