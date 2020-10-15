#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
int n, m, rt, cnt, ans;
map<int, int> mp;
struct tree
{
    int l;
    int r;
    int fa;
    int L;
    int R;
    int siz;
} tr[300005];
bool which(int u)
{
    return tr[tr[u].fa].r == u;
}
void pushup(int u)
{
    tr[u].siz = tr[tr[u].l].siz + tr[tr[u].r].siz + tr[u].R - tr[u].L + 1;
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
void splay(int u)
{
    while (tr[u].fa)
    {
        if (tr[tr[u].fa].fa)
        {
            if (which(u) == which(tr[u].fa))
                rotate(tr[u].fa);
            else
                rotate(u);
        }
        rotate(u);
    }
    pushup(u);
    rt = u;
    return;
}
void ins(int u, int L, int R)
{
    tr[u].L = L;
    tr[u].R = R;
    return;
}
int findmin(int u)
{
    while (tr[u].l)
        u = tr[u].l;
    return u;
}
int findmax(int u)
{
    while (tr[u].r)
        u = tr[u].r;
    return u;
}
void insl(int u)
{
    splay(findmin(rt));
    tr[rt].l = u;
    tr[u].fa = rt;
    pushup(rt);
    return;
}
void insr(int u)
{
    splay(findmax(rt));
    tr[rt].r = u;
    tr[u].fa = rt;
    pushup(rt);
    return;
}
void join(int u, int v)
{
    int w = findmax(u);
    splay(w);
    tr[w].r = v;
    tr[v].fa = w;
    pushup(w);
    return;
}
void cut(int u)
{
    splay(u);
    tr[tr[u].l].fa = 0;
    tr[tr[u].r].fa = 0;
    if (!tr[u].l || !tr[u].r)
    {
        rt = tr[u].l | tr[u].r;
        tr[u].l = 0;
        tr[u].r = 0;
        tr[u].siz = tr[u].R - tr[u].L + 1;
        return;
    }
    join(tr[u].l, tr[u].r);
    tr[u].l = 0;
    tr[u].r = 0;
    tr[u].siz = tr[u].R - tr[u].L + 1;
    return;
}
void split(int u, int w, int val)
{
    splay(u);
    int L = tr[u].L, R = tr[u].R;
    mp[R] = 0;
    ins(u, val, val);
    mp[val] = u;
    if (L <= w - 1)
    {
        ++cnt;
        ins(cnt, L, w - 1);
        if (tr[u].l)
        {
            tr[cnt].l = tr[u].l;
            tr[tr[u].l].fa = cnt;
        }
        tr[u].l = cnt;
        tr[cnt].fa = u;
        mp[w - 1] = cnt;
        pushup(cnt);
    }
    if (R >= w + 1)
    {
        ++cnt;
        ins(cnt, w + 1, R);
        if (tr[u].r)
        {
            tr[cnt].r = tr[u].r;
            tr[tr[u].r].fa = cnt;
        }
        tr[u].r = cnt;
        tr[cnt].fa = u;
        mp[R] = cnt;
        pushup(cnt);
    }
    pushup(u);
    return;
}
int pos(int u)
{
    splay(u);
    return tr[tr[u].l].siz + 1;
}
int apos(int k)
{
    int u = rt;
    while (k <= tr[tr[u].l].siz || k > tr[tr[u].l].siz + tr[u].R - tr[u].L + 1)
    {
        if (k <= tr[tr[u].l].siz)
            u = tr[u].l;
        else
        {
            k -= tr[tr[u].l].siz + tr[u].R - tr[u].L + 1;
            u = tr[u].r;
        }
    }
    k -= tr[tr[u].l].siz;
    splay(u);
    return tr[u].L + k - 1;
}
int main()
{
    scanf("%d%d", &n, &m);
    rt = 1;
    ++cnt;
    ins(cnt, 1, n);
    tr[1].siz = n;
    mp[n] = cnt;
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            x -= ans;
            y -= ans;
            int u = (*mp.lower_bound(x)).second;
            split(u, x, y);
            ans = pos(u);
        }
        else if (type == 2)
        {
            int x;
            scanf("%d", &x);
            x -= ans;
            int u = (*mp.lower_bound(x)).second;
            split(u, x, x);
            ans = pos(u);
            cut(u);
            insl(u);
        }
        else if (type == 3)
        {
            int x;
            scanf("%d", &x);
            x -= ans;
            int u = (*mp.lower_bound(x)).second;
            split(u, x, x);
            ans = pos(u);
            cut(u);
            insr(u);
        }
        else if (type == 4)
        {
            int k;
            scanf("%d", &k);
            k -= ans;
            ans = apos(k);
        }
        printf("%d\n", ans);
    }
    return 0;
}