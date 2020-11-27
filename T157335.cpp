#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
#define pii pair<int, int>
#define mp make_pair
typedef long long ll;
int n, m, X;
int a[100005];
struct tree
{
    int l;
    int r;
    ll num;
    vector<pii> vec[2];
} tr[400005];
tree pushup(tree &x, tree &y)
{
    tree z;
    z.l = x.l;
    z.r = y.r;
    z.num = x.num + y.num;
    for (int i = 0; i < x.vec[0].size(); ++i)
        z.vec[0].push_back(x.vec[0][i]);
    for (int i = 0; i < y.vec[0].size(); ++i)
        if (z.vec[0][z.vec[0].size() - 1].second < (z.vec[0][z.vec[0].size() - 1].second | y.vec[0][i].second))
            z.vec[0].push_back(mp(y.vec[0][i].first, z.vec[0][z.vec[0].size() - 1].second | y.vec[0][i].second));
    for (int i = 0; i < y.vec[1].size(); ++i)
        z.vec[1].push_back(y.vec[1][i]);
    for (int i = 0; i < x.vec[1].size(); ++i)
        if (z.vec[1][z.vec[1].size() - 1].second < (z.vec[1][z.vec[1].size() - 1].second | x.vec[1][i].second))
            z.vec[1].push_back(mp(x.vec[1][i].first, z.vec[1][z.vec[1].size() - 1].second | x.vec[1][i].second));
    int j = 0;
    for (int i = x.vec[1].size() - 1; i >= 0; --i)
    {
        while (j < y.vec[0].size() && (x.vec[1][i].second | y.vec[0][j].second) < X)
            ++j;
        if (j < y.vec[0].size())
            if (i + 1 == x.vec[1].size())
                z.num += (ll)(x.vec[1][i].first - x.l + 1) * (y.r - y.vec[0][j].first + 1);
            else
                z.num += (ll)(x.vec[1][i].first - x.vec[1][i + 1].first) * (y.r - y.vec[0][j].first + 1);
    }
    return z;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        if (a[l] >= X)
            tr[id].num = 1;
        tr[id].vec[0].push_back(mp(l, a[l]));
        tr[id].vec[1].push_back(mp(l, a[l]));
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id] = pushup(tr[lch], tr[rch]);
    return;
}
void add(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        if (val >= X)
            tr[id].num = 1;
        else
            tr[id].num = 0;
        tr[id].vec[0].clear();
        tr[id].vec[0].push_back(mp(w, val));
        tr[id].vec[1].clear();
        tr[id].vec[1].push_back(mp(w, val));
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    else
        add(rch, w, val);
    tr[id] = pushup(tr[lch], tr[rch]);
    return;
}
tree ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    tree x = ask(lch, l, mid);
    tree y = ask(rch, mid + 1, r);
    return pushup(x, y);
}
int main()
{
    scanf("%d%d%d", &n, &m, &X);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, u, v;
        scanf("%d%d%d", &opt, &u, &v);
        if (opt == 1)
            add(1, u, v);
        else
            printf("%lld\n", ask(1, u, v).num);
    }
    return 0;
}