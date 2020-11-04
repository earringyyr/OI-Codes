#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, c, q, sum, tot, rt, cnt, opt, ans;
int head[100005], dep[100005];
int st[100005], ed[100005];
int minx[100005][2], maxn[100005][2];
struct edge
{
    int v;
    int nxt;
} e[100005];
struct node
{
    int x[2];
} a[100005], p[100005];
struct tree
{
    int l;
    int r;
    int c;
    int lazy;
} tr[100005];
void ins(int u, int v)
{
    ++sum;
    e[sum].v = v;
    e[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    ++tot;
    st[k] = tot;
    a[k].x[0] = tot;
    a[k].x[1] = dep[k];
    int d = head[k];
    while (d)
    {
        dep[e[d].v] = dep[k] + 1;
        dfs(e[d].v);
        d = e[d].nxt;
    }
    ed[k] = tot;
    return;
}
bool cmp(node aa, node bb)
{
    return aa.x[opt] < bb.x[opt];
}
int solve(int l, int r)
{
    double sum[2][2] = {0};
    for (int i = l; i <= r; ++i)
    {
        sum[0][0] += (ll)a[i].x[0] * a[i].x[0];
        sum[0][1] += a[i].x[0];
        sum[1][0] += (ll)a[i].x[1] * a[i].x[1];
        sum[1][1] += a[i].x[1];
    }
    return sum[0][0] * (r - l + 1) - sum[0][1] * sum[0][1] < sum[1][0] * (r - l + 1) - sum[1][1] * sum[1][1];
}
void build(int &id, int l, int r)
{
    if (l > r)
        return;
    id = ++cnt;
    tr[id].l = 0;
    tr[id].r = 0;
    tr[id].c = 1;
    tr[id].lazy = 0;
    int mid = (l + r) >> 1;
    opt = solve(l, r);
    nth_element(a + l, a + mid, a + r + 1, cmp);
    build(tr[id].l, l, mid - 1);
    build(tr[id].r, mid + 1, r);
    p[id] = a[mid];
    minx[id][0] = a[mid].x[0];
    maxn[id][0] = a[mid].x[0];
    minx[id][1] = a[mid].x[1];
    maxn[id][1] = a[mid].x[1];
    if (tr[id].l)
    {
        minx[id][0] = min(minx[id][0], minx[tr[id].l][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].l][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].l][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].l][1]);
    }
    if (tr[id].r)
    {
        minx[id][0] = min(minx[id][0], minx[tr[id].r][0]);
        maxn[id][0] = max(maxn[id][0], maxn[tr[id].r][0]);
        minx[id][1] = min(minx[id][1], minx[tr[id].r][1]);
        maxn[id][1] = max(maxn[id][1], maxn[tr[id].r][1]);
    }
    return;
}
void pushdown(int id)
{
    if (tr[id].lazy)
    {
        if (tr[id].l)
        {
            tr[tr[id].l].c = tr[id].lazy;
            tr[tr[id].l].lazy = tr[id].lazy;
        }
        if (tr[id].r)
        {
            tr[tr[id].r].c = tr[id].lazy;
            tr[tr[id].r].lazy = tr[id].lazy;
        }
        tr[id].lazy = 0;
    }
    return;
}
void change(int id, int l0, int r0, int l1, int r1, int co)
{
    if (minx[id][0] >= l0 && maxn[id][0] <= r0 && minx[id][1] >= l1 && maxn[id][1] <= r1)
    {
        tr[id].c = co;
        tr[id].lazy = co;
        return;
    }
    pushdown(id);
    if (p[id].x[0] >= l0 && p[id].x[0] <= r0 && p[id].x[1] >= l1 && p[id].x[1] <= r1)
        tr[id].c = co;
    if (tr[id].l)
        if (minx[tr[id].l][0] <= r0 && maxn[tr[id].l][0] >= l0)
            if (minx[tr[id].l][1] <= r1 && maxn[tr[id].l][1] >= l1)
                change(tr[id].l, l0, r0, l1, r1, co);
    if (tr[id].r)
        if (minx[tr[id].r][0] <= r0 && maxn[tr[id].r][0] >= l0)
            if (minx[tr[id].r][1] <= r1 && maxn[tr[id].r][1] >= l1)
                change(tr[id].r, l0, r0, l1, r1, co);
    return;
}
int query(int id, int x, int y)
{
    if (p[id].x[0] == x && p[id].x[1] == y)
        return tr[id].c;
    pushdown(id);
    if (tr[id].l)
        if (minx[tr[id].l][0] <= x && maxn[tr[id].l][0] >= x && minx[tr[id].l][1] <= y && maxn[tr[id].l][1] >= y)
        {
            int tmp = query(tr[id].l, x, y);
            if (tmp)
                return tmp;
        }
    if (tr[id].r)
        if (minx[tr[id].r][0] <= x && maxn[tr[id].r][0] >= x && minx[tr[id].r][1] <= y && maxn[tr[id].r][1] >= y)
        {
            int tmp = query(tr[id].r, x, y);
            if (tmp)
                return tmp;
        }
    return 0;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        sum = 0;
        cnt = 0;
        tot = 0;
        memset(head, 0, sizeof(head));
        scanf("%d%d%d", &n, &c, &q);
        for (int i = 2; i <= n; ++i)
        {
            int fa;
            scanf("%d", &fa);
            ins(fa, i);
        }
        dfs(1);
        build(rt, 1, n);
        for (int i = 1; i <= q; ++i)
        {
            int a, l, c;
            scanf("%d%d%d", &a, &l, &c);
            if (c == 0)
                ans = (ans + (ll)i * query(rt, st[a], dep[a]) % mod) % mod;
            else
                change(rt, st[a], ed[a], dep[a], dep[a] + l, c);
        }
        printf("%d\n", ans);
    }
    return 0;
}