#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define mod 1000000007
#define int long long
using namespace std;
int t, n, m, xx, tot, sum, cnt, les, equ;
int fa[100005][25], maxn[100005][25];
int head[100005], nxt[200005], to[200005], w[200005], mo[100005], dep[100005];
int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        ch = getchar();
        if (ch == '-')
            f = -1;
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int find(int x)
{
    if (x == mo[x])
        return x;
    return mo[x] = find(mo[x]);
}
void add(int a, int b, int c)
{
    nxt[++tot] = head[a];
    head[a] = tot;
    to[tot] = b;
    w[tot] = c;
    nxt[++tot] = head[b];
    head[b] = tot;
    to[tot] = a;
    w[tot] = c;
}
void dfs(int u, int faa)
{
    dep[u] = dep[faa] + 1;
    fa[u][0] = faa;
    for (int i = 1; i <= 20; ++i)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 1; i <= 20; ++i)
        maxn[u][i] = max(maxn[u][i - 1], maxn[fa[u][i - 1]][i - 1]);
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == faa)
            continue;
        maxn[v][0] = w[i];
        dfs(v, u);
    }
}
int query(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
    int tmp = 0;
    for (int i = 20; i >= 0; --i)
    {
        if (dep[fa[a][i]] >= dep[b])
        {
            tmp = max(tmp, maxn[a][i]);
            a = fa[a][i];
        }
    }
    if (a == b)
        return tmp;
    for (int i = 20; i >= 0; --i)
    {
        if (fa[a][i] != fa[b][i])
        {
            tmp = max(tmp, max(maxn[a][i], maxn[b][i]));
            a = fa[a][i], b = fa[b][i];
        }
    }
    return max(tmp, max(maxn[a][0], maxn[b][0]));
}
struct node
{
    int u, v, w, lazy;
    void init()
    {
        lazy = 0;
    }
} e[200005];
bool cmp(node a, node b)
{
    return a.w < b.w;
}
int ksm(int a, int k)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = b * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return b;
}
int solve()
{
    sum = 0;
    cnt = 0;
    les = 0;
    equ = 0;
    for (int i = 1; i <= m; ++i)
    {
        int x = find(e[i].u), y = find(e[i].v);
        if (x != y)
        {
            ++cnt;
            sum += e[i].w;
            mo[x] = y;
            e[i].lazy = 1;
            add(e[i].u, e[i].v, e[i].w);
            if (cnt == n - 1)
                break;
        }
    }
    if (sum > xx)
        return 0;
    dfs(1, 0);
    int now = sum;
    for (int i = 1; i <= m; ++i)
    {
        if (!e[i].lazy)
        {
            now = sum + e[i].w - query(e[i].u, e[i].v);
            if (now == xx)
                equ++;
            if (now < xx)
                les++;
        }
    }
    int ans = 0;
    if (sum == xx)
        ans = (ans + (ksm(2, m) - 2 * ksm(2, m - n + 1 - equ) % mod + mod) % mod) % mod;
    else
        ans = (ans + 2 * (ksm(2, m - n + 1 - les) - ksm(2, m - n + 1 - les - equ) + mod) % mod) % mod;
    return ans;
}
signed main()
{
    t = read();
    for (int tt = 1; tt <= t; ++tt)
    {
        tot = 0;
        memset(head, 0, sizeof(head));
        n = read();
        m = read();
        xx = read();
        for (int i = 1; i <= n; ++i)
            mo[i] = i;
        for (int i = 1; i <= m; ++i)
        {
            e[i].lazy = 0;
            e[i].u = read();
            e[i].v = read();
            e[i].w = read();
        }
        sort(e + 1, e + m + 1, cmp);
        printf("%lld\n", solve());
    }
    return 0;
}