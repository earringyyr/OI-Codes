#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define mod 1000000007
#define int long long
using namespace std;
int n, k, q, a[50005], c[25], s[25], ans[200005], f[25][50005];
struct node
{
    int id;
    int l;
    int r;
    node(int aa, int bb, int cc)
    {
        id = aa;
        l = bb;
        r = cc;
    }
};
vector<node> vec;
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= k)
    {
        c[x] = (c[x] + val) % mod;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans = (ans + c[x]) % mod;
        x -= lowbit(x);
    }
    return ans;
}
void solve(int l, int r, vector<node> v)
{
    if (l == r)
    {
        int siz = v.size();
        for (int i = 0; i < siz; ++i)
            ans[v[i].id] = 2;
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = 1; i <= k; ++i)
    {
        memset(c, 0, sizeof(c));
        for (int j = mid; j >= l; --j)
        {
            f[i][j] = ask(k + 1 - a[j]);
            if (a[j] == i)
                f[i][j] = (f[i][j] + 1) % mod;
            add(k + 1 - a[j], f[i][j]);
        }
        for (int j = mid - 1; j >= l; --j)
            f[i][j] = (f[i][j] + f[i][j + 1]) % mod;
    }
    for (int i = 1; i <= k; ++i)
    {
        memset(c, 0, sizeof(c));
        for (int j = mid + 1; j <= r; ++j)
        {
            f[i][j] = ask(a[j]);
            if (a[j] == i)
                f[i][j] = (f[i][j] + 1) % mod;
            add(a[j], f[i][j]);
        }
        for (int j = mid + 2; j <= r; ++j)
            f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
    }
    for (int i = l; i <= mid; ++i)
        f[1][i] = (f[1][i] + 1) % mod;
    for (int i = mid + 1; i <= r; ++i)
        f[k][i] = (f[k][i] + 1) % mod;
    vector<node> va, vb;
    int siz = v.size();
    for (int i = 0; i < siz; ++i)
    {
        if (v[i].r <= mid)
            va.push_back(v[i]);
        else if (v[i].l >= mid + 1)
            vb.push_back(v[i]);
        else
        {
            memset(s, 0, sizeof(s));
            for (int j = k; j >= 1; --j)
                s[j] = (s[j + 1] + f[j][v[i].r]) % mod;
            for (int j = 1; j <= k; ++j)
                ans[v[i].id] = (ans[v[i].id] + f[j][v[i].l] * s[j] % mod) % mod;
        }
    }
    if (va.size())
        solve(l, mid, va);
    if (vb.size())
        solve(mid + 1, r, vb);
    return;
}
signed main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    scanf("%lld", &q);
    for (int i = 1; i <= q; ++i)
    {
        int l, r;
        scanf("%lld%lld", &l, &r);
        vec.push_back(node(i, l, r));
    }
    solve(1, n, vec);
    for (int i = 1; i <= q; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}