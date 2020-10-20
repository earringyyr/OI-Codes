#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define int long long
#define lch id << 1
#define rch id << 1 | 1
int n, m, mod, c, base = 20000;
int a[50005];
int phi[105], c1[105][20005], c2[105][20005];
int num[50005], b[50005][105], jc[105];
struct tree
{
    int l;
    int r;
    int cnt;
    int num;
} tr[200005];
void dfs(int p)
{
    phi[++phi[0]] = p;
    if (p == 1)
        return;
    int pp = p, res = p;
    for (int i = 2; i * i <= p; ++i)
        if (pp % i == 0)
        {
            while (pp % i == 0)
                pp /= i;
            res = res / i * (i - 1);
        }
    if (pp > 1)
        res = res / pp * (pp - 1);
    dfs(res);
    return;
}
int ksm(int k, int id)
{
    return c1[id][k / base] * c2[id][k % base] % phi[id];
}
int f(int i, int j, int k)
{
    if (k == 1)
        return 0;
    if (!j)
        return a[i] % phi[k];
    if (c == 1 || (j - 1 <= num[i] && b[i][j - 1] < phi[k - 1]))
        return ksm(f(i, j - 1, k - 1), k);
    return ksm(f(i, j - 1, k - 1) + phi[k - 1], k);
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
void change(int id, int l, int r)
{
    if (tr[id].cnt > phi[0])
        return;
    if (tr[id].l == tr[id].r)
    {
        ++tr[id].cnt;
        tr[id].num = f(l, tr[id].cnt, phi[0]);
        return;
    }
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        change(lch, l, r);
    if (l >= mid + 1)
        change(rch, l, r);
    if (l <= mid && r >= mid + 1)
    {
        change(lch, l, mid);
        change(rch, mid + 1, r);
    }
    tr[id].cnt = min(tr[lch].cnt, tr[rch].cnt);
    tr[id].num = (tr[lch].num + tr[rch].num) % mod;
    return;
}
int query(int id, int l, int r)
{
    if (tr[id].l == l && tr[id].r == r)
        return tr[id].num;
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (r <= mid)
        return query(lch, l, r);
    if (l >= mid + 1)
        return query(rch, l, r);
    return (query(lch, l, mid) + query(rch, mid + 1, r)) % mod;
}
signed main()
{
    scanf("%lld%lld%lld%lld", &n, &m, &mod, &c);
    dfs(mod);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    reverse(phi + 1, phi + phi[0] + 1);
    for (int i = 1; i <= phi[0]; ++i)
    {
        c1[i][0] = 1;
        c2[i][0] = 1;
        for (int j = 1; j < base; ++j)
            c2[i][j] = c2[i][j - 1] * c % phi[i];
        c1[i][1] = c2[i][base - 1] * c % phi[i];
        for (int j = 2; j < base; ++j)
            c1[i][j] = c1[i][j - 1] * c1[i][1] % phi[i];
    }
    jc[0] = 1;
    for (int i = 1; i <= 100; ++i)
    {
        jc[i] = jc[i - 1] * c;
        if (jc[i] <= 100000000)
            ++num[0];
        else
            break;
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i][0] = a[i];
        for (int j = 1; j <= 100; ++j)
        {
            if (b[i][j - 1] <= num[0])
            {
                b[i][j] = jc[b[i][j - 1]];
                ++num[i];
            }
            else
                break;
        }
    }
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int type, l, r;
        scanf("%lld%lld%lld", &type, &l, &r);
        if (type == 0)
            change(1, l, r);
        else
            printf("%lld\n", query(1, l, r));
    }
    return 0;
}