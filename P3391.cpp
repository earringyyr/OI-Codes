#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, rt, tot;
struct node
{
    int l;
    int r;
    int fa;
    int siz;
    int val;
    int num;
} tr[100005];
void pushup(int u)
{
    tr[u].siz = tr[tr[u].l].siz + tr[tr[u].r].siz + 1;
    return;
}
void pushdown(int u)
{
    if (tr[u].num)
    {
        tr[u].num = 0;
        tr[tr[u].l].num ^= 1;
        tr[tr[u].r].num ^= 1;
        swap(tr[u].l, tr[u].r);
    }
    return;
}
bool which(int u)
{
    return tr[tr[u].fa].r == u;
}
void rotate(int u)
{
    int v = tr[u].fa;
    int w = tr[v].fa;
    int b = (tr[v].l == u ? tr[u].r : tr[u].l);
    tr[u].fa = w;
    tr[v].fa = u;
    if (b)
        tr[b].fa = v;
    if (w)
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
    pushup(v);
    return;
}
void splay(int u, int tar)
{
    while (tr[u].fa != tar)
    {
        if (tr[tr[u].fa].fa != tar)
        {
            if (which(u) == which(tr[u].fa))
                rotate(tr[u].fa);
            else
                rotate(u);
        }
        rotate(u);
    }
    pushup(u);
    if (!tar)
        rt = u;
    return;
}
void insert(int val)
{
    int u = rt, v = 0, dir;
    while (u)
    {
        ++tr[u].siz;
        v = u;
        if (val < tr[u].val)
        {
            dir = 0;
            u = tr[u].l;
        }
        else
        {
            dir = 1;
            u = tr[u].r;
        }
    }
    u = ++tot;
    tr[u].val = val;
    tr[u].fa = v;
    tr[u].siz = 1;
    if (v)
        (dir == 0 ? tr[v].l : tr[v].r) = u;
    splay(u, 0);
    return;
}
int find(int val)
{
    int u = rt;
    while (1)
    {
        pushdown(u);
        if (tr[tr[u].l].siz >= val)
            u = tr[u].l;
        else if (tr[tr[u].l].siz == val - 1)
            break;
        else
        {
            val -= tr[tr[u].l].siz + 1;
            u = tr[u].r;
        }
    }
    return u;
}
void rev(int l, int r)
{
    int u = find(l), v = find(r);
    splay(u, 0);
    splay(v, u);
    swap(tr[u].val, tr[v].val);
    tr[tr[v].l].num ^= 1;
    return;
}
void dfs(int k)
{
    pushdown(k);
    if (tr[k].l)
        dfs(tr[k].l);
    printf("%d ", tr[k].val);
    if (tr[k].r)
        dfs(tr[k].r);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        insert(i);
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l < r)
            rev(l, r);
    }
    dfs(rt);
    return 0;
}