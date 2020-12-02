#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int unsigned long long
const int mod = 2148473648;
int n, m, l, sum, d, base = 1, hh = 1, tt = 1, pos = 1, cnt, Ans;
int head[5000005], ans[2][5000005];
int len[5000005], f[5000005], son[5000005];
int c[5000005], q[5000005];
struct node
{
    int v;
    int nxt;
} a[5000005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs1(int k)
{
    int d = head[k];
    while (d)
    {
        dfs1(a[d].v);
        if (len[a[d].v] > len[son[k]])
            son[k] = a[d].v;
        d = a[d].nxt;
    }
    len[k] = len[son[k]] + 1;
    return;
}
void dfs2(int k)
{
    int d = head[k];
    while (d)
    {
        if (a[d].v == son[k])
            f[a[d].v] = f[k] + 1;
        else
            f[a[d].v] = 1;
        dfs2(a[d].v);
        d = a[d].nxt;
    }
    return;
}
signed main()
{
    scanf("%llu%llu%llu", &n, &m, &l);
    for (int i = 2; i <= n; ++i)
    {
        int u, v = i;
        scanf("%llu", &u);
        ins(u, i);
    }
    dfs1(1);
    f[1] = 1;
    dfs2(1);
    q[1] = 1;
    f[1] = 0;
    c[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        ans[0][i] = ans[0][i - 1];
        int tmp = tt;
        for (int j = hh; j <= tt; ++j)
        {
            int k = q[j];
            int d = head[k];
            if (!head[k])
                continue;
            --c[f[k]];
            if (f[k] >= pos)
            {
                --cnt;
                (ans[0][i] += (mod - f[k])) %= mod;
            }
            while (d)
            {
                q[++tmp] = a[d].v;
                ++c[f[a[d].v]];
                if (f[a[d].v] >= pos)
                {
                    ++cnt;
                    (ans[0][i] += f[a[d].v]) %= mod;
                }
                d = a[d].nxt;
            }
        }
        hh = tt + 1;
        tt = tmp;
        ans[1][i] = ans[0][i];
        while (cnt > l)
        {
            if (cnt - l < c[pos])
            {
                (ans[1][i] += (mod - (cnt - l) * pos % mod)) %= mod;
                break;
            }
            else
            {
                (ans[0][i] += (mod - c[pos] * pos % mod)) %= mod;
                ans[1][i] = ans[0][i];
                cnt -= c[pos];
                ++pos;
            }
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        base = base * 233 % mod;
        scanf("%llu", &d);
        Ans = (Ans + ans[1][d] * base % mod) % mod;
    }
    printf("%llu", (Ans + mod) % mod);
    return 0;
}