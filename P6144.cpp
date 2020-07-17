#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lch id << 1
#define rch id << 1 | 1
#define mod 1000000007
using namespace std;
typedef long long ll;
int n, k, ans, num[3][15], c[15][15];
struct node
{
    int l;
    int r;
} a[100005];
struct tree
{
    int l;
    int r;
    int lazy;
    int f[15];
} tr[800005];
inline int my_mod(int x)
{
    if (x > mod)
        x -= mod;
    return x;
}
inline void pushdown(int id)
{
    if (tr[id].lazy == 1)
        return;
    if (tr[id].l != tr[id].r)
    {
        int lazy = tr[id].lazy;
        tr[id].lazy = 1;
        tr[lch].lazy = ((ll)tr[lch].lazy * lazy) % mod;
        tr[rch].lazy = ((ll)tr[rch].lazy * lazy) % mod;
        for (register int i = 0; i <= k; ++i)
        {
            tr[lch].f[i] = ((ll)tr[lch].f[i] * lazy) % mod;
            tr[rch].f[i] = ((ll)tr[rch].f[i] * lazy) % mod;
        }
    }
    return;
}
inline void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy = 1;
    if (l == r)
    {
        if (l == 0)
            tr[id].f[0] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    if (l == 0)
        tr[id].f[0] = 1;
    return;
}
inline int query(int id, int l, int r, int k)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].f[k];
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r, k);
    if (l >= mid + 1)
        return query(rch, l, r, k);
    return my_mod(query(lch, l, mid, k) + query(rch, mid + 1, r, k));
}
inline void add(int id, int w, int pos)
{
    pushdown(id);
    if (tr[id].l == tr[id].r)
    {
        for (register int i = 0; i <= k; ++i)
        {
            num[1][i] = query(1, 0, a[pos].l - 1, i);
            num[2][i] = query(1, a[pos].l, a[pos].r, i);
        }
        if (!num[1][0])
            num[1][0] = 1;
        for (register int i = 0; i <= k; ++i)
        {
            for (register int j = 0; j <= i; ++j)
            {
                int tmp = (ll)c[i][j] * num[1][j] % mod;
                tr[id].f[i] = my_mod(tr[id].f[i] + tmp);
            }
            tr[id].f[i] = my_mod(tr[id].f[i] + num[2][i]);
        }
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, pos);
    if (w >= mid + 1)
        add(rch, w, pos);
    for (register int i = 0; i <= k; ++i)
        tr[id].f[i] = my_mod(tr[lch].f[i] + tr[rch].f[i]);
    return;
}
inline void mul(int id, int l, int r, int val)
{
    pushdown(id);
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].lazy = ((ll)tr[id].lazy * val) % mod;
        for (int i = 0; i <= k; ++i)
            tr[id].f[i] = ((ll)tr[id].f[i] * val) % mod;
        return;
    }
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
    for (register int i = 0; i <= k; ++i)
        tr[id].f[i] = my_mod(tr[lch].f[i] + tr[rch].f[i]);
    return;
}
inline bool cmp(node aa, node bb)
{
    return aa.l < bb.l;
}
int main()
{
    for (register int i = 0; i <= 10; ++i)
    {
        c[i][0] = 1;
        for (register int j = 1; j <= i; ++j)
            c[i][j] = my_mod(c[i - 1][j - 1] + c[i - 1][j]);
    }
    scanf("%d%d", &n, &k);
    for (register int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1, cmp);
    build(1, 0, 2 * n);
    for (register int i = 1; i <= n; ++i)
    {
        add(1, a[i].r, i);
        if (a[i].r < 2 * n)
            mul(1, a[i].r + 1, 2 * n, 2);
    }
    printf("%d", tr[1].f[k]);
    return 0;
}