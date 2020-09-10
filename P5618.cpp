#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, m, w[3][60005];
struct tree
{
    int l;
    int r;
    int num;
    int lval;
    int rval;
    int lmax;
    int rmax;
    int maxn;
    int ans;
} tr[240005];
void pushup(int id)
{
    tr[id].num = tr[lch].num + tr[rch].num;
    tr[id].lval = tr[lch].lval;
    tr[id].rval = tr[rch].rval;
    tr[id].lmax = tr[lch].lmax;
    tr[id].rmax = tr[rch].rmax;
    tr[id].maxn = max(max(w[1][tr[lch].r], w[2][tr[rch].l]), max(tr[lch].maxn, tr[rch].maxn));
    int del = max(max(w[1][tr[lch].r], w[2][tr[rch].l]), max(tr[lch].rmax, tr[rch].lmax));
    tr[id].ans = tr[lch].ans + tr[rch].ans + w[1][tr[lch].r] + w[2][tr[rch].l] - del;
    if (del == tr[lch].rval)
    {
        --tr[id].num;
        if (tr[lch].num == 1)
        {
            tr[id].lval = tr[rch].lval;
            tr[id].lmax = max(max(w[1][tr[lch].r], w[2][tr[rch].l]), max(tr[lch].maxn, tr[rch].lmax));
        }
        return;
    }
    if (del == tr[rch].lval)
    {
        --tr[id].num;
        if (tr[rch].num == 1)
        {
            tr[id].rval = tr[lch].rval;
            tr[id].rmax = max(max(w[1][tr[lch].r], w[2][tr[rch].l]), max(tr[rch].maxn, tr[lch].rmax));
        }
        return;
    }
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = 1;
        tr[id].lval = w[0][l];
        tr[id].rval = w[0][l];
        tr[id].lmax = w[0][l];
        tr[id].rmax = w[0][l];
        tr[id].ans = w[0][l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    pushup(id);
    return;
}
void change_1(int id, int pos)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].lval = w[0][pos];
        tr[id].rval = w[0][pos];
        tr[id].lmax = w[0][pos];
        tr[id].rmax = w[0][pos];
        tr[id].ans = w[0][pos];
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (pos <= mid)
        change_1(lch, pos);
    else
        change_1(rch, pos);
    pushup(id);
    return;
}
void change_2(int id, int l, int r)
{
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change_2(lch, l, r);
    if (l >= mid + 1)
        change_2(rch, l, r);
    pushup(id);
    return;
}
tree query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    tree L = query(lch, l, mid);
    tree R = query(rch, mid + 1, r);
    tree now;
    now.l = l;
    now.r = r;
    now.num = L.num + R.num;
    now.lval = L.lval;
    now.rval = R.rval;
    now.lmax = L.lmax;
    now.rmax = R.rmax;
    now.maxn = max(max(w[1][L.r], w[2][R.l]), max(L.maxn, R.maxn));
    int del = max(max(w[1][L.r], w[2][R.l]), max(L.rmax, R.lmax));
    now.ans = L.ans + R.ans + w[1][L.r] + w[2][R.l] - del;
    if (del == L.rval)
    {
        --now.num;
        if (L.num == 1)
        {
            now.lval = R.lval;
            now.lmax = max(max(w[1][L.r], w[2][R.l]), max(L.maxn, R.lmax));
        }
        return now;
    }
    if (del == R.lval)
    {
        --now.num;
        if (R.num == 1)
        {
            now.rval = L.rval;
            now.rmax = max(max(w[1][L.r], w[2][R.l]), max(R.maxn, L.rmax));
        }
        return now;
    }
    return now;
}
signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
        scanf("%d", &w[1][i]);
    for (int i = 2; i <= n; ++i)
        scanf("%d", &w[2][i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[0][i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'C')
        {
            int x0, y0, x1, y1, ww;
            scanf("%d%d%d%d%d", &x0, &y0, &x1, &y1, &ww);
            if (y0 == y1)
            {
                w[0][y0] = ww;
                change_1(1, y0);
            }
            else
            {
                if (y0 > y1)
                    swap(y0, y1);
                if (x0 == 1)
                    w[1][y0] = ww;
                else
                    w[2][y1] = ww;
                change_2(1, y0, y1);
            }
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, l, r).ans);
        }
    }
    return 0;
}