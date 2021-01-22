#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, sum, rt, top, ans;
int val[1000005];
int head[1000005], st[1000005];
int siz[1000005], son[1000005];
int f[1000005][2];
struct edge
{
    int v;
    int nxt;
} a[2000005];
struct matrix
{
    int a[2][2];
    matrix(int aa = 0, int bb = 0, int cc = 0, int dd = 0)
    {
        a[0][0] = aa;
        a[0][1] = bb;
        a[1][0] = cc;
        a[1][1] = dd;
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    cc.a[i][j] = max(cc.a[i][j], a[i][k] + bb.a[k][j]);
        return cc;
    }
} A[1000005], B[1000005];
struct tree
{
    int fa;
    int l;
    int r;
} tr[1000005];
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
    f[k][1] = val[k];
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            f[k][0] += max(f[a[d].v][0], f[a[d].v][1]);
            f[k][1] += f[a[d].v][0];
            if (!son[k] || siz[a[d].v] > siz[son[k]])
                son[k] = a[d].v;
        }
        d = a[d].nxt;
    }
    return;
}
void pushup(int k)
{
    B[k] = A[k];
    if (tr[k].l)
        B[k] = B[tr[k].l] * B[k];
    if (tr[k].r)
        B[k] = B[k] * B[tr[k].r];
    return;
}
int build(int l, int r)
{
    if (l > r)
        return 0;
    int cnt = 0, tot = 0;
    for (int i = l; i <= r; ++i)
        cnt += siz[st[i]];
    for (int i = l; i <= r; ++i)
    {
        tot += siz[st[i]];
        if (tot * 2 >= cnt)
        {
            tr[st[i]].l = build(l, i - 1);
            tr[st[i]].r = build(i + 1, r);
            tr[tr[st[i]].l].fa = st[i];
            tr[tr[st[i]].r].fa = st[i];
            pushup(st[i]);
            return st[i];
        }
    }
    return 0;
}
int dfs2(int k, int fa)
{
    int tmp = k;
    while (k)
    {
        siz[k] -= siz[son[k]];
        f[k][0] -= max(f[son[k]][0], f[son[k]][1]);
        f[k][1] -= f[son[k]][0];
        A[k] = matrix(f[k][0], f[k][0], f[k][1], -inf);
        int d = head[k];
        while (d)
        {
            if (a[d].v != fa && a[d].v != son[k])
                tr[dfs2(a[d].v, k)].fa = k;
            d = a[d].nxt;
        }
        fa = k;
        k = son[k];
    }
    k = tmp;
    top = 0;
    while (k)
    {
        st[++top] = k;
        k = son[k];
    }
    return build(1, top);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ins(u, v);
        ins(v, u);
    }
    dfs1(1, 0);
    rt = dfs2(1, 0);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        x ^= ans;
        y -= val[x];
        A[x].a[1][0] += y;
        int tmp = x;
        while (x)
        {
            if (tr[x].fa && tr[tr[x].fa].l != x && tr[tr[x].fa].r != x)
            {
                A[tr[x].fa].a[0][0] -= max(max(B[x].a[0][0], B[x].a[0][1]), max(B[x].a[1][0], B[x].a[1][1]));
                A[tr[x].fa].a[0][1] -= max(max(B[x].a[0][0], B[x].a[0][1]), max(B[x].a[1][0], B[x].a[1][1]));
                A[tr[x].fa].a[1][0] -= max(B[x].a[0][0], B[x].a[0][1]);
                pushup(x);
                A[tr[x].fa].a[0][0] += max(max(B[x].a[0][0], B[x].a[0][1]), max(B[x].a[1][0], B[x].a[1][1]));
                A[tr[x].fa].a[0][1] += max(max(B[x].a[0][0], B[x].a[0][1]), max(B[x].a[1][0], B[x].a[1][1]));
                A[tr[x].fa].a[1][0] += max(B[x].a[0][0], B[x].a[0][1]);
            }
            else
                pushup(x);
            x = tr[x].fa;
        }
        x = tmp;
        val[x] += y;
        ans = max(max(B[rt].a[0][0], B[rt].a[0][1]), max(B[rt].a[1][0], B[rt].a[1][1]));
        printf("%d\n", ans);
    }
    return 0;
}