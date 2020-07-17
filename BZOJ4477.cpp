#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, q, sum, cnt, ans;
int lg[100005], head[100005], dep[100005];
int rt[100005], fa[100005][20];
string s[100005];
struct tree
{
    int sum;
    int son[26];
} tr[100005 * 20];
struct node
{
    int v;
    int w;
    int nxt;
} a[200005];
void ins(int u, int v, int w)
{
    ++sum;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void build(int y, int &x, int t, int val)
{
    x = ++cnt;
    tr[x] = tr[y];
    ++tr[x].sum;
    if (s[val][t] < 'a' || s[val][t] > 'z')
        return;
    build(tr[y].son[s[val][t] - 'a'], tr[x].son[s[val][t] - 'a'], t + 1, val);
    return;
}
void dfs(int k)
{
    for (int i = 1; i <= lg[dep[k]]; ++i)
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
    int d = head[k];
    while (d)
    {
        if (!dep[a[d].v])
        {
            dep[a[d].v] = dep[k] + 1;
            fa[a[d].v][0] = k;
            build(rt[k], rt[a[d].v], 0, a[d].w);
            dfs(a[d].v);
        }
        d = a[d].nxt;
    }
    return;
}
int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    while (dep[u] > dep[v])
        u = fa[u][lg[dep[u] - dep[v]]];
    if (u == v)
        return u;
    for (int i = lg[dep[u]]; i >= 0; --i)
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
int query(int id, int t, string ss)
{
    if (ss[t] < 'a' || ss[t] > 'z')
        return tr[id].sum;
    if (!tr[id].son[ss[t] - 'a'])
        return 0;
    return query(tr[id].son[ss[t] - 'a'], t + 1, ss);
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        cin >> s[i];
        ins(u, v, i);
        ins(v, u, i);
    }
    dfs(1);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int u, v;
        string ss;
        scanf("%d%d", &u, &v);
        cin >> ss;
        int len = ss.length(), f = lca(u, v);
        ans = 0;
        ans += query(rt[u], 0, ss);
        ans += query(rt[v], 0, ss);
        ans -= 2 * query(rt[f], 0, ss);
        printf("%d\n", ans);
    }
    return 0;
}