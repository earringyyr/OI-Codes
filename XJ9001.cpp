#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
const int mod = 998244353;
int n, l, r, cnt, num, ans;
int vis[500005], inv[500005];
struct node
{
    int pos;
    int num;
} a[500005];
struct tree
{
    int l;
    int r;
    int num;
    int numl;
    int numr;
} tr[2000005];
bool cmp(node aa, node bb)
{
    return aa.num > bb.num;
}
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
        tr[id].numl = inv[0];
        tr[id].numr = inv[0];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    tr[id].numl = ((ll)tr[lch].numl * inv[tr[rch].num] % mod + tr[rch].numl) % mod;
    tr[id].numr = ((ll)tr[rch].numr * inv[tr[rch].num] % mod + tr[lch].numr) % mod;
    return;
}
void add(int id, int w)
{
    if (tr[id].l == tr[id].r)
    {
        ++tr[id].num;
        tr[id].numl = inv[1];
        tr[id].numr = inv[1];
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w);
    else
        add(rch, w);
    tr[id].num = tr[lch].num + tr[rch].num;
    tr[id].numl = ((ll)tr[lch].numl * inv[tr[rch].num] % mod + tr[rch].numl) % mod;
    tr[id].numr = ((ll)tr[rch].numr * inv[tr[lch].num] % mod + tr[lch].numr) % mod;
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
    tree L = ask(lch, l, mid), R = ask(rch, mid + 1, r);
    tree M = tr[id];
    M.num = L.num + R.num;
    M.numl = ((ll)L.numl * inv[R.num] % mod + R.numl) % mod;
    M.numr = ((ll)R.numr * inv[L.num] % mod + L.numr) % mod;
    return M;
}
int main()
{
    scanf("%d", &n);
    int tmp = ksm(2, mod - 2);
    inv[0] = 1;
    for (int i = 1; i <= n; ++i)
        inv[i] = (ll)inv[i - 1] * tmp % mod;
    for (int i = 1; i <= n; ++i)
    {
        a[i].pos = i;
        scanf("%d", &a[i].num);
    }
    sort(a + 1, a + n + 1, cmp);
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        ans = (ans + (ll)a[i].num * ask(1, 1, a[i].pos).numl % mod * ask(1, a[i].pos, n).numr % mod * inv[1] % mod) % mod;
        add(1, a[i].pos);
    }
    printf("%d", ans);
    return 0;
}