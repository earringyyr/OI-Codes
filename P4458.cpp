#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
const int mod = 1000000007;
int n, m, inv2, a[200005], sum[200005][3];
struct tree
{
    int l;
    int r;
    int num;
    int lazy[3];
} tr[800005];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
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
    for (int i = 0; i < 3; ++i)
    {
        tr[lch].lazy[i] = (tr[lch].lazy[i] + tr[id].lazy[i]) % mod;
        tr[rch].lazy[i] = (tr[rch].lazy[i] + tr[id].lazy[i]) % mod;
        tr[lch].num = (tr[lch].num + (ll)(sum[tr[lch].r][i] - sum[tr[lch].l - 1][i] + mod) * tr[id].lazy[i] % mod) % mod;
        tr[rch].num = (tr[rch].num + (ll)(sum[tr[rch].r][i] - sum[tr[rch].l - 1][i] + mod) * tr[id].lazy[i] % mod) % mod;
        tr[id].lazy[i] = 0;
    }
    return;
}
void add(int id, int l, int r, int val, int type)
{
    if (tr[id].l == l && tr[id].r == r)
    {
        tr[id].lazy[type] = (tr[id].lazy[type] + val) % mod;
        tr[id].num = (tr[id].num + (ll)(sum[r][type] - sum[l - 1][type] + mod) * val % mod) % mod;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        add(lch, l, r, val, type);
    if (l >= mid + 1)
        add(rch, l, r, val, type);
    if (l <= mid && r >= mid + 1)
    {
        add(lch, l, mid, val, type);
        add(rch, mid + 1, r, val, type);
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
    inv2 = ksm(2, mod - 2);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        sum[i][0] = sum[i - 1][0] + 1;
        sum[i][1] = (sum[i - 1][1] + i) % mod;
        sum[i][2] = (sum[i - 1][2] + (ll)i * i % mod) % mod;
    }
    for (int i = 1; i <= n; ++i)
        a[i] = (a[i - 1] + a[i]) % mod;
    for (int i = 1; i <= n; ++i)
        a[i] = (a[i - 1] + a[i]) % mod;
    build(1, 0, n);
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            if (u > v)
                swap(u, v);
            add(1, u, v, (ll)d * inv2 % mod, 2);
            add(1, u, v, (ll)d * inv2 % mod * (3 - 2 * u + mod) % mod, 1);
            add(1, u, v, (ll)d * inv2 % mod * ((ll)u * u % mod - 3 * u + 2 + mod) % mod, 0);
            if (v < n)
            {
                add(1, v + 1, n, (ll)d * (v - u + 1) % mod, 1);
                add(1, v + 1, n, (ll)d * inv2 % mod * (((ll)u * u % mod - (ll)v * v % mod + mod + v - 3 * u + 2 + mod) % mod) % mod, 0);
            }
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", (int)(((ll)(r - l + 1) * ask(1, n, n) % mod - ask(1, l - 1, r - 1) + mod - ask(1, n - r, n - l) + mod) % mod));
        }
    }
    return 0;
}