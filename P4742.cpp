#include <iostream>
#include <cstdio>
#define mod 1000000007
#define lch id << 1
#define rch id << 1 | 1
using namespace std;
int n, q, a[500005], b[500005];
struct node
{
    int l;
    int r;
    int a;
    int b;
} tr[2000005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    if (l == r)
    {
        tr[id].a = a[l];
        tr[id].b = b[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].a = (long long)tr[lch].a * tr[rch].a % mod;
    tr[id].b = ((long long)tr[rch].a * tr[lch].b % mod + tr[rch].b) % mod;
    return;
}
void change(int id, int w, int aa, int bb)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].a = aa;
        tr[id].b = bb;
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        change(lch, w, aa, bb);
    else
        change(rch, w, aa, bb);
    tr[id].a = (long long)tr[lch].a * tr[rch].a % mod;
    tr[id].b = ((long long)tr[rch].a * tr[lch].b % mod + tr[rch].b) % mod;
    return;
}
int query(int id, int l, int r, int val)
{
    if (tr[id].l == l && tr[id].r == r)
        return ((long long)tr[id].a * val % mod + tr[id].b) % mod;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r, val);
    if (l >= mid + 1)
        return query(rch, l, r, val);
    if (l <= mid && r >= mid + 1)
    {
        val = query(lch, l, mid, val);
        return query(rch, mid + 1, r, val);
    }
}
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i], &b[i]);
    build(1, 1, n);
    for (int i = 1; i <= q; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'Q')
        {
            int k;
            scanf("%d", &k);
            printf("%d\n", query(1, 1, k, 1));
        }
        else
        {
            int k, aa, bb;
            scanf("%d%d%d", &k, &aa, &bb);
            change(1, k, aa, bb);
        }
    }
    return 0;
}