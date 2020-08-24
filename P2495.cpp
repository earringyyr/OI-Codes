#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf = 0x7fffffffffffffff;
int n, m, sum, cnt, tail, h[250005];
int head[250005], st[250005], flg[250005];
int fa[250005], siz[250005], son[250005];
int dep[250005], dfn[250005], top[250005];
ll dis[250005], f[250005];
struct node
{
    int v;
    int w;
    int nxt;
} a[500005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool cmp(int aa, int bb)
{
    return dfn[aa] < dfn[bb];
}
void dfs1(int k, int f)
{
    fa[k] = f;
    siz[k] = 1;
    son[k] = -1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
            dis[a[d].v] = min(dis[k], (ll)a[d].w);
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            if (son[k] == -1 || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
}
void dfs2(int k, int topf)
{
    dfn[k] = ++cnt;
    top[k] = topf;
    if (son[k] != -1)
        dfs2(son[k], topf);
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa[k] && a[d].v != son[k])
            dfs2(a[d].v, a[d].v);
        d = a[d].nxt;
    }
}
int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    return u;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        f[k] += min((ll)a[d].w, f[a[d].v]);
        f[a[d].v] = 0;
        d = a[d].nxt;
    }
    head[k] = 0;
    if (flg[k])
        f[k] = inf;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        ins(u, v, w);
        ins(v, u, w);
    }
    memset(dis, 0x7f, sizeof(dis));
    dfs1(1, 0);
    dfs2(1, 1);
    memset(head, 0, sizeof(head));
    scanf("%d", &m);
    for (int T = 1; T <= m; ++T)
    {
        sum = 0;
        tail = 0;
        int k;
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i)
        {
            scanf("%d", &h[i]);
            flg[h[i]] = 1;
        }
        sort(h + 1, h + k + 1, cmp);
        if (h[1] != 1)
            st[++tail] = 1;
        for (int i = 1; i <= k; ++i)
        {
            if (!tail)
            {
                st[++tail] = h[i];
                continue;
            }
            int lca = LCA(st[tail], h[i]);
            if (lca == st[tail])
            {
                st[++tail] = h[i];
                continue;
            }
            while (tail > 1 && dep[st[tail - 1]] >= dep[lca])
            {
                ins(st[tail - 1], st[tail], dis[st[tail]]);
                --tail;
            }
            if (st[tail] == lca)
                st[++tail] = h[i];
            else
            {
                ins(lca, st[tail], dis[st[tail]]);
                --tail;
                st[++tail] = lca;
                st[++tail] = h[i];
            }
        }
        while (tail > 1)
        {
            ins(st[tail - 1], st[tail], dis[st[tail]]);
            --tail;
        }
        dfs(1);
        printf("%lld\n", f[1]);
        f[1] = 0;
        for (int i = 1; i <= k; ++i)
            flg[h[i]] = 0;
    }
    return 0;
}