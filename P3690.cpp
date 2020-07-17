#include <iostream>
#include <cstdio>
using namespace std;
int n, m;
struct node
{
    int l;
    int r;
    int fa;
    int num;
    int sum;
    int tag;
} tr[100005];
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
    tr[u].sum = tr[tr[u].l].sum ^ tr[tr[u].r].sum ^ tr[u].num;
    return;
}
void reverse(int u)
{
    swap(tr[u].l, tr[u].r);
    tr[u].tag ^= 1;
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
    int st[100005], top = 0, id = u;
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
    {
        int a;
        scanf("%d", &a);
        tr[i].num = a;
        tr[i].sum = a;
    }
    for (int i = 1; i <= m; ++i)
    {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);
        if (type == 0)
        {
            split(x, y);
            printf("%d\n", tr[y].sum);
        }
        if (type == 1)
            link(x, y);
        if (type == 2)
            cut(x, y);
        if (type == 3)
        {
            splay(x);
            tr[x].num = y;
        }
    }
    return 0;
}