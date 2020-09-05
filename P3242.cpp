#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n, p, Q, sum, cnt;
int head[40005], st[40005], ed[40005];
int lg[40005], dep[40005], fa[40005][20];
int u[40005], v[40005], k[40005];
int q[40005], q1[40005], q2[40005], ans[40005];
struct node
{
    int v;
    int nxt;
} a[80005];
struct plate
{
    int u;
    int v;
    int w;
} b[40005];
struct point
{
    int x;
    int y;
    int val;
    point(int xx = 0, int yy = 0, int zz = 0)
    {
        x = xx;
        y = yy;
        val = zz;
    }
};
struct bit
{
    int siz;
    point tr[400005];
    int c[40005];
    int lowbit(int x)
    {
        return x & -x;
    }
    void add(int x, int val)
    {
        while (x <= n + 1)
        {
            c[x] += val;
            x += lowbit(x);
        }
        return;
    }
    int query(int x)
    {
        int num = 0;
        while (x >= 1)
        {
            num += c[x];
            x -= lowbit(x);
        }
        return num;
    }
} T;
bool cmp(plate aa, plate bb)
{
    return aa.w < bb.w;
}
bool comp(int aa, int bb)
{
    return st[u[aa]] < st[u[bb]];
}
bool camp(point aa, point bb)
{
    return aa.x < bb.x;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k, int f)
{
    fa[k][0] = f;
    for (int i = 1; i <= lg[dep[k]]; ++i)
        fa[k][i] = fa[fa[k][i - 1]][i - 1];
    st[k] = ++cnt;
    int d = head[k];
    while (d)
    {
        if (a[d].v != f)
        {
            dep[a[d].v] = dep[k] + 1;
            dfs(a[d].v, k);
        }
        d = a[d].nxt;
    }
    ed[k] = cnt;
    return;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = lg[dep[u] - dep[v]]; i >= 0; --i)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
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
int get_z(int u, int v)
{
    for (int i = lg[dep[v] - dep[u]]; i >= 0; --i)
        if (dep[fa[v][i]] > dep[u])
            v = fa[v][i];
    return v;
}
void solve(int l, int r, int L, int R)
{
    if (L > R)
        return;
    if (l == r)
    {
        for (int i = L; i <= R; ++i)
            ans[q[i]] = b[l].w;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = l; i <= mid; ++i)
    {
        int lca = LCA(b[i].u, b[i].v);
        if (lca == b[i].u)
        {
            int z = get_z(b[i].u, b[i].v);
            T.tr[++T.siz] = point(1, st[b[i].v], 1);
            T.tr[++T.siz] = point(1, ed[b[i].v] + 1, -1);
            T.tr[++T.siz] = point(st[z], st[b[i].v], -1);
            T.tr[++T.siz] = point(st[z], ed[b[i].v] + 1, 1);
            T.tr[++T.siz] = point(st[b[i].v], ed[z] + 1, 1);
            T.tr[++T.siz] = point(st[b[i].v], n + 1, -1);
            T.tr[++T.siz] = point(ed[b[i].v] + 1, ed[z] + 1, -1);
            T.tr[++T.siz] = point(ed[b[i].v] + 1, n + 1, 1);
        }
        else
        {
            T.tr[++T.siz] = point(st[b[i].u], st[b[i].v], 1);
            T.tr[++T.siz] = point(st[b[i].u], ed[b[i].v] + 1, -1);
            T.tr[++T.siz] = point(ed[b[i].u] + 1, st[b[i].v], -1);
            T.tr[++T.siz] = point(ed[b[i].u] + 1, ed[b[i].v] + 1, 1);
        }
    }
    int pos = 1;
    sort(T.tr + 1, T.tr + T.siz + 1, camp);
    for (int i = L; i <= R; ++i)
    {
        while (pos <= T.siz && T.tr[pos].x <= st[u[q[i]]])
        {
            T.add(T.tr[pos].y, T.tr[pos].val);
            ++pos;
        }
        int tmp = T.query(st[v[q[i]]]);
        if (tmp >= k[q[i]])
            q1[++cnt1] = q[i];
        else
        {
            k[q[i]] -= tmp;
            q2[++cnt2] = q[i];
        }
    }
    while (pos <= T.siz)
    {
        T.add(T.tr[pos].y, T.tr[pos].val);
        ++pos;
    }
    T.siz = 0;
    for (int i = 1; i <= cnt1; ++i)
        q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i)
        q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1);
    solve(mid + 1, r, L + cnt1, R);
    return;
}
int main()
{
    scanf("%d%d%d", &n, &p, &Q);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    dep[1] = 1;
    dfs(1, 0);
    for (int i = 1; i <= p; ++i)
    {
        scanf("%d%d%d", &b[i].u, &b[i].v, &b[i].w);
        if (st[b[i].u] > st[b[i].v])
            swap(b[i].u, b[i].v);
    }
    sort(b + 1, b + p + 1, cmp);
    for (int i = 1; i <= Q; ++i)
    {
        scanf("%d%d%d", &u[i], &v[i], &k[i]);
        if (st[u[i]] > st[v[i]])
            swap(u[i], v[i]);
        q[i] = i;
    }
    sort(q + 1, q + Q + 1, comp);
    solve(1, p, 1, Q);
    for (int i = 1; i <= Q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}