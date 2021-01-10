#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
int n, m, ans = inf;
int fa[50005];
struct edge
{
    int u;
    int v;
    int a;
    int b;
} a[100005];
struct tree
{
    int l;
    int r;
    int fa;
    int tag;
    int num;
    int sum;
} tr[150005];
bool cmp(edge aa, edge bb)
{
    return aa.a < bb.a;
}
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
bool which(int u)
{
    return tr[tr[u].fa].r == u;
}
bool notroot(int u)
{
    return tr[tr[u].fa].l == u || tr[tr[u].fa].r == u;
}
void pushup(int u)
{
    tr[u].sum = max(tr[u].num, max(tr[tr[u].l].sum, tr[tr[u].r].sum));
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
    int st[150005], top = 0, id = u;
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
void access(int u)
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
    return;
}
void makeroot(int u)
{
    access(u);
    splay(u);
    reverse(u);
    return;
}
int findroot(int u)
{
    access(u);
    splay(u);
    while (tr[u].l)
    {
        pushdown(u);
        u = tr[u].l;
    }
    splay(u);
    return u;
}
void split(int u, int v)
{
    makeroot(u);
    access(v);
    splay(v);
    return;
}
void link(int u, int v)
{
    makeroot(u);
    if (findroot(v) != u)
        tr[u].fa = v;
    return;
}
void cut(int u, int v)
{
    makeroot(u);
    if (findroot(v) == u && tr[v].fa == u && !tr[v].l)
    {
        tr[v].fa = 0;
        tr[u].r = 0;
        pushup(u);
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &a[i].u, &a[i].v, &a[i].a, &a[i].b);
    sort(a + 1, a + m + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        tr[i + n].num = a[i].b;
        tr[i + n].sum = a[i].b;
        int u = a[i].u, v = a[i].v;
        if (getfather(u) != getfather(v))
        {
            fa[getfather(u)] = getfather(v);
            link(u, i + n);
            link(i + n, v);
        }
        else
        {
            split(u, v);
            int w = tr[tr[v].l].sum;
            if (w > a[i].b)
            {
                int k = tr[v].l;
                while (tr[k].num != w)
                {
                    if (tr[tr[k].l].sum == w)
                        k = tr[k].l;
                    else
                        k = tr[k].r;
                }
                cut(a[k - n].u, k);
                cut(k, a[k - n].v);
                link(u, i + n);
                link(i + n, v);
            }
        }
        if (getfather(1) == getfather(n))
        {
            split(1, n);
            ans = min(ans, a[i].a + tr[tr[n].l].sum);
        }
    }
    if (ans == inf)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}