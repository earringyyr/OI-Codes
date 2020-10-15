#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
#define lch id << 1
#define rch id << 1 | 1
int n, m, st = 1, a[150005];
unordered_map<int, int> num;
struct tree
{
    int l;
    int r;
    int minx;
    int num;
    int lazy;
} tr[2400005];
void pushup(int id)
{
    tr[id].minx = min(tr[lch].minx, tr[rch].minx);
    tr[id].num = 0;
    if (tr[id].minx == tr[lch].minx)
        tr[id].num += tr[lch].num;
    if (tr[id].minx == tr[rch].minx)
        tr[id].num += tr[rch].num;
    return;
}
void pushdown(int id)
{
    int lazy = tr[id].lazy;
    tr[id].lazy = 0;
    tr[lch].minx += lazy;
    tr[rch].minx += lazy;
    tr[lch].lazy += lazy;
    tr[rch].lazy += lazy;
    return;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].num = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    pushup(id);
    return;
}
void add(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].minx += val;
        tr[id].lazy += val;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val);
    if (l >= mid + 1)
        add(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val);
        add(rch, mid + 1, r, val);
    }
    pushup(id);
    return;
}
tree ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id];
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    tree F, L, R;
    L = ask(lch, l, mid);
    R = ask(rch, mid + 1, r);
    F.minx = min(L.minx, R.minx);
    F.num = 0;
    if (L.minx == F.minx)
        F.num += L.num;
    if (R.minx == F.minx)
        F.num += R.num;
    return F;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        ++num[a[i]];
    }
    build(1, 1 - m - n + 1, n + m);
    for (int i = 1; i <= n; ++i)
        if (num[i])
            add(1, i - num[i] + 1, i, 1);
    for (int i = 1; i <= m; ++i)
    {
        int p, x;
        scanf("%d%d", &p, &x);
        if (p == 0)
        {
            if (x == -1)
            {
                if (num[st])
                    add(1, st - num[st] + 1, st, -1);
                ++st;
                if (num[st + n - 1])
                    add(1, st + n - 1 - num[st + n - 1] + 1, st + n - 1, 1);
            }
            else
            {
                if (num[st + n - 1])
                    add(1, st + n - 1 - num[st + n - 1] + 1, st + n - 1, -1);
                --st;
                if (num[st])
                    add(1, st - num[st] + 1, st, 1);
            }
        }
        else
        {
            if (a[p] >= st && a[p] <= st + n - 1)
                add(1, a[p] - num[a[p]] + 1, a[p] - num[a[p]] + 1, -1);
            --num[a[p]];
            a[p] = st + x - 1;
            ++num[a[p]];
            if (a[p] >= st && a[p] <= st + n - 1)
                add(1, a[p] - num[a[p]] + 1, a[p] - num[a[p]] + 1, 1);
        }
        tree rt = ask(1, st, st + n - 1);
        if (rt.minx > 0)
            printf("0\n");
        else
            printf("%d\n", rt.num);
    }
    return 0;
}