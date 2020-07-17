#include <iostream>
#include <cstdio>
using namespace std;
int n, tot, root;
struct node
{
    int l;
    int r;
    int fa;
    int val;
    int size;
    int num;
} tr[100005];
bool which(int u)
{
    return tr[tr[u].fa].r == u;
}
void pushup(int u)
{
    tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].num;
    return;
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
        root = u;
    return;
}
void insert(int val)
{
    int u = root, v = 0, dir;
    while (u)
    {
        v = u;
        tr[u].size++;
        if (val == tr[u].val)
        {
            tr[u].num++;
            pushup(u);
            return;
        }
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
    tr[u].size = 1;
    tr[u].val = val;
    tr[u].num = 1;
    tr[u].fa = v;
    if (v)
        (dir == 0 ? tr[v].l : tr[v].r) = u;
    splay(u, 0);
    return;
}
int findmax(int u)
{
    if (u)
        while (tr[u].r)
            u = tr[u].r;
    return u;
}
void join(int u, int v)
{
    int w = findmax(u);
    splay(w, 0);
    tr[w].r = v;
    tr[v].fa = w;
    pushup(w);
    return;
}
void cut(int val)
{
    int u = root;
    while (tr[u].val != val)
    {
        if (val < tr[u].val)
            u = tr[u].l;
        else
            u = tr[u].r;
    }
    splay(u, 0);
    tr[u].num--;
    pushup(u);
    if (tr[u].num)
        return;
    if (!tr[u].l && !tr[u].r)
        root = 0;
    else if (!tr[u].l || !tr[u].r)
    {
        root = tr[u].l + tr[u].r;
        tr[root].fa = 0;
    }
    else
    {
        tr[tr[u].l].fa = 0;
        tr[tr[u].r].fa = 0;
        join(tr[u].l, tr[u].r);
    }
    return;
}
int pos(int val)
{
    int ans = 1, u = root;
    while (tr[u].val != val)
    {
        if (val < tr[u].val)
            u = tr[u].l;
        else
        {
            ans += (tr[u].num + tr[tr[u].l].size);
            u = tr[u].r;
        }
    }
    ans += tr[tr[u].l].size;
    splay(u, 0);
    return ans;
}
int apos(int x)
{
    int u = root;
    while (x <= tr[tr[u].l].size || x > tr[tr[u].l].size + tr[u].num)
    {
        if (x <= tr[tr[u].l].size)
            u = tr[u].l;
        else
        {
            x -= (tr[tr[u].l].size + tr[u].num);
            u = tr[u].r;
        }
    }
    return tr[u].val;
}
int pre(int val)
{
    int ans = -100000000, u = root;
    while (u)
    {
        if (tr[u].val < val && tr[u].val > ans)
            ans = tr[u].val;
        if (val > tr[u].val)
            u = tr[u].r;
        else
            u = tr[u].l;
    }
    return ans;
}
int suff(int val)
{
    int ans = 100000000, u = root;
    while (u)
    {
        if (tr[u].val > val && tr[u].val < ans)
            ans = tr[u].val;
        if (val < tr[u].val)
            u = tr[u].l;
        else
            u = tr[u].r;
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int opt, x;
        scanf("%d%d", &opt, &x);
        switch (opt)
        {
        case 1:
            insert(x);
            break;
        case 2:
            cut(x);
            break;
        case 3:
            printf("%d\n", pos(x));
            break;
        case 4:
            printf("%d\n", apos(x));
            break;
        case 5:
            printf("%d\n", pre(x));
            break;
        case 6:
            printf("%d\n", suff(x));
            break;
        }
    }
    return 0;
}