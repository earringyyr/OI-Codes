#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define lch id << 1
#define rch id << 1 | 1
typedef long long ll;
const int mod = 998244353;
int n, m, q, a[100005], type[100005], p[100005], v[100005];
vector<int> vec[100005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
struct tree
{
    int l;
    int r;
    int num;
    int lazy;
} tr[400005];
void build(int id, int l, int r)
{
    tr[id].l = l;
    tr[id].r = r;
    tr[id].lazy = 1;
    if (l == r)
    {
        tr[id].num = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lch, l, mid);
    build(rch, mid + 1, r);
    return;
}
void pushdown(int id)
{
    int lazy = tr[id].lazy;
    tr[lch].lazy = (ll)tr[lch].lazy * lazy % mod;
    tr[rch].lazy = (ll)tr[rch].lazy * lazy % mod;
    tr[lch].num = (ll)tr[lch].num * lazy % mod;
    tr[rch].num = (ll)tr[rch].num * lazy % mod;
    tr[id].lazy = 1;
    return;
}
void add(int id, int w, int val)
{
    if (tr[id].l == tr[id].r)
    {
        tr[id].num = (tr[id].num + val) % mod;
        return;
    }
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        add(lch, w, val);
    else
        add(rch, w, val);
    return;
}
int ask(int id, int w)
{
    if (tr[id].l == tr[id].r)
        return tr[id].num;
    pushdown(id);
    int mid = (tr[id].l + tr[id].r) >> 1;
    if (w <= mid)
        return ask(lch, w);
    else
        return ask(rch, w);
}
void dfs(int k)
{
    if (type[k] == 1)
        add(1, p[k], v[k]);
    else if (type[k] == 2)
    {
        tr[1].lazy = (ll)tr[1].lazy * v[k] % mod;
        tr[1].num = (ll)tr[1].num * v[k] % mod;
    }
    else if (type[k] == 3)
    {
        int siz = vec[k].size();
        for (int i = 0; i < siz; ++i)
            dfs(vec[k][i]);
    }
    return;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    build(1, 1, n);
    m = read();
    for (int i = 1; i <= m; ++i)
    {
        type[i] = read();
        if (type[i] == 1)
        {
            p[i] = read();
            v[i] = read();
        }
        else if (type[i] == 2)
            v[i] = read();
        else if (type[i] == 3)
        {
            int c;
            c = read();
            for (int j = 1; j <= c; ++j)
            {
                int tmp;
                tmp = read();
                vec[i].push_back(tmp);
            }
        }
    }
    q = read();
    for (int i = 1; i <= q; ++i)
    {
        int f;
        f = read();
        dfs(f);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", ask(1, i));
    return 0;
}