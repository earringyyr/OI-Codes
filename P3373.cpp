#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
int n, m, mod;
int a[100005];
struct tree
{
    int l;
    int r;
    int num;
    int lazy_add;
    int lazy_mul;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy_mul = 1;
    if (l == r)
    {
        tr[id].num = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].num = (tr[lch].num + tr[rch].num) % mod;
    return;
}
void pushdown(int id)
{
    int lazy_add = tr[id].lazy_add;
    int lazy_mul = tr[id].lazy_mul;
    tr[id].lazy_add = 0;
    tr[id].lazy_mul = 1;
    tr[lch].num = ((ll)tr[lch].num * lazy_mul + (ll)(tr[lch].r - tr[lch].l + 1) * lazy_add) % mod;
    tr[lch].lazy_mul = (ll)tr[lch].lazy_mul * lazy_mul % mod;
    tr[lch].lazy_add = ((ll)tr[lch].lazy_add * lazy_mul % mod + lazy_add) % mod;
    tr[rch].num = ((ll)tr[rch].num * lazy_mul + (ll)(tr[rch].r - tr[rch].l + 1) * lazy_add) % mod;
    tr[rch].lazy_mul = (ll)tr[rch].lazy_mul * lazy_mul % mod;
    tr[rch].lazy_add = ((ll)tr[rch].lazy_add * lazy_mul % mod + lazy_add) % mod;
    return;
}
void add(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = (tr[id].num + (ll)(tr[id].r - tr[id].l + 1) * val % mod) % mod;
        tr[id].lazy_add = (tr[id].lazy_add + val) % mod;
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
    tr[id].num = (tr[lch].num + tr[rch].num) % mod;
    return;
}
void mul(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].num = (ll)tr[id].num * val % mod;
        tr[id].lazy_add = (ll)tr[id].lazy_add * val % mod;
        tr[id].lazy_mul = (ll)tr[id].lazy_mul * val % mod;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        mul(lch, l, r, val);
    if (l >= mid + 1)
        mul(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        mul(lch, l, mid, val);
        mul(rch, mid + 1, r, val);
    }
    tr[id].num = (tr[lch].num + tr[rch].num) % mod;
    return;
}
int ask(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return ask(lch, l, r);
    if (l >= mid + 1)
        return ask(rch, l, r);
    return (ask(lch, l, mid) + ask(rch, mid + 1, r)) % mod;
}
int main()
{
    scanf("%d%d%d", &n, &m, &mod);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);
        if (type == 1)
        {
            int k;
            scanf("%d", &k);
            mul(1, x, y, k);
        }
        else if (type == 2)
        {
            int k;
            scanf("%d", &k);
            add(1, x, y, k);
        }
        else
            printf("%d\n", ask(1, x, y));
    }
    return 0;
}