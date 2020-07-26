#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
namespace lct
{
    struct tree
    {
        int l;
        int r;
        int fa;
        int tag;
        int siz;
        int num;
    } tr[400005];
    int st[400005], sum = 0;
    void newnode(int u)
    {
        ++sum;
        tr[sum].siz = u;
        tr[sum].num = u;
        return;
    }
    bool notroot(int u)
    {
        return tr[tr[u].fa].l == u || tr[tr[u].fa].r == u;
    }
    bool which(int u)
    {
        return tr[tr[u].fa].r == u;
    }
    void pushup(int u)
    {
        tr[u].num = tr[tr[u].l].num + tr[tr[u].r].num + tr[u].siz;
        return;
    }
    void reverse(int u)
    {
        swap(tr[u].l, tr[u].r);
        tr[u].tag ^= 1;
        return;
    }
    void pushdown(int u)
    {
        if (tr[u].tag)
        {
            if (tr[u].l)
                reverse(tr[u].l);
            if (tr[u].r)
                reverse(tr[u].r);
            tr[u].tag = 0;
        }
        return;
    }
    void rotate(int u)
    {
        int v = tr[u].fa;
        int w = tr[v].fa;
        int b = (tr[v].l == u ? tr[u].r : tr[u].l);
        if (notroot(v))
            (tr[w].l == v ? tr[w].l : tr[w].r) = u;
        if (tr[v].l == u)
        {
            tr[u].r = v;
            tr[v].l = b;
        }
        else
        {
            tr[u].l = v;
            tr[v].r = b;
        }
        tr[u].fa = w;
        tr[v].fa = u;
        if (b)
            tr[b].fa = v;
        pushup(v);
        return;
    }
    void splay(int u)
    {
        int top = 0, id = u;
        st[++top] = id;
        while (notroot(id))
        {
            id = tr[id].fa;
            st[++top] = id;
        }
        for (int i = top; i >= 1; --i)
            pushdown(st[i]);
        while (notroot(u))
        {
            if (notroot(tr[u].fa))
            {
                if (which(u) == which(tr[u].fa))
                    rotate(tr[u].fa);
                else
                    rotate(u);
            }
            rotate(u);
        }
        pushup(u);
        return;
    }
    int access(int u)
    {
        int v = 0;
        while (u)
        {
            splay(u);
            tr[u].r = v;
            pushup(u);
            v = u;
            u = tr[u].fa;
        }
        return v;
    }
    void link(int u, int v)
    {
        splay(u);
        tr[u].fa = v;
        return;
    }
    void cut(int u)
    {
        access(u);
        splay(u);
        tr[tr[u].l].fa = 0;
        tr[u].l = 0;
        pushup(u);
        return;
    }
} // namespace lct
using namespace lct;
int n, m, cnt = 1, num, now;
int l[200005], r[200005], b[200005], ans[200005], vis[200005];
struct node
{
    node(int aa = 0, int bb = 0, int cc = 0, int dd = 0)
    {
        id = aa;
        x = bb;
        y = cc;
        pos = dd;
    }
    int id;
    int x;
    int y;
    int pos;
} q[400005];
bool cmp(node aa, node bb)
{
    if (aa.pos != bb.pos)
        return aa.pos < bb.pos;
    return aa.id < bb.id;
}
int main()
{
    scanf("%d%d", &n, &m);
    newnode(1);
    newnode(0);
    link(2, 1);
    l[1] = 1;
    r[1] = n;
    b[1] = 1;
    now = 2;
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 0)
        {
            newnode(1);
            ++cnt;
            b[cnt] = sum;
            link(sum, now);
            scanf("%d%d", &l[cnt], &r[cnt]);
        }
        else if (type == 1)
        {
            int L, R, x;
            scanf("%d%d%d", &L, &R, &x);
            if (x > cnt)
                continue;
            L = max(L, l[x]);
            R = min(R, r[x]);
            if (L > R)
                continue;
            newnode(0);
            link(sum, now);
            q[++num] = node(i - m, sum, b[x], L);
            q[++num] = node(i - m, sum, now, R + 1);
            now = sum;
        }
        else if (type == 2)
        {
            int x, u, v;
            scanf("%d%d%d", &x, &u, &v);
            vis[i] = 1;
            q[++num] = node(i, b[u], b[v], x);
        }
    }
    sort(q + 1, q + num + 1, cmp);
    int j = 1;
    for (int i = 1; i <= n; ++i)
        while (j <= num && q[j].pos == i)
        {
            if (q[j].id <= 0)
            {
                cut(q[j].x);
                link(q[j].x, q[j].y);
            }
            else
            {
                access(q[j].x);
                splay(q[j].x);
                ans[q[j].id] += tr[q[j].x].num;
                int lca = access(q[j].y);
                splay(q[j].y);
                ans[q[j].id] += tr[q[j].y].num;
                access(lca);
                splay(lca);
                ans[q[j].id] -= tr[lca].num * 2;
            }
            ++j;
        }
    for (int i = 1; i <= m; ++i)
        if (vis[i])
            printf("%d\n", ans[i]);
    return 0;
}