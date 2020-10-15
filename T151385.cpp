#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, sum, ans;
int head[300005], siz[300005], f[300005];
int sum1[300005], sum2[300005];
int sun1[300005], sun2[300005];
struct node
{
    int v;
    int nxt;
} a[600005];
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
int F(int k)
{
    int num = 1;
    for (int i = k / 2 + 1; i <= k; ++i)
        num = (ll)num * i % mod * ((mod + 1) / 2) % mod;
    return num;
}
void dfs1(int k, int fa)
{
    siz[k] = 1;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            dfs1(a[d].v, k);
            siz[k] += siz[a[d].v];
            sum1[k] = (sum1[k] + sum1[a[d].v]) % mod;
            sum2[k] = (sum2[k] + sum2[a[d].v]) % mod;
        }
        d = a[d].nxt;
    }
    sum1[k] = (sum1[k] + siz[k]) % mod;
    sum2[k] = (sum2[k] + (ll)siz[k] * siz[k] % mod) % mod;
    return;
}
void dfs2(int k, int fa)
{
    int A, B1, B2;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            sun1[a[d].v] = ((((sun1[k] + sum1[k]) % mod - sum1[a[d].v] + mod) % mod - siz[k] + mod) % mod + (n - siz[a[d].v])) % mod;
            sun2[a[d].v] = ((((sun2[k] + sum2[k]) % mod - sum2[a[d].v] + mod) % mod - (ll)siz[k] * siz[k] % mod + mod) % mod + (ll)(n - siz[a[d].v]) * (n - siz[a[d].v])) % mod;
            A = n - siz[a[d].v];
            B1 = sum1[a[d].v];
            B2 = sum2[a[d].v];
            ans = (ans + (ll)f[n - 2] * B1 % mod * A % mod) % mod;
            ans = (ans + (ll)f[n - 4] * B2 % mod * A % mod * A % mod) % mod;
            ans = (ans + (ll)f[n - 4] * (((ll)n * n % mod - 3 * n + 1 + mod) % mod) % mod * B1 % mod * A % mod) % mod;
            ans = (ans - (ll)f[n - 4] * (n - 2 + mod) % mod * B1 % mod * A % mod * A % mod + mod) % mod;
            ans = (ans - (ll)f[n - 4] * (n - 2 + mod) % mod * B2 % mod * A % mod + mod) % mod;
            A = siz[a[d].v];
            B1 = (sun1[a[d].v] - (n - siz[a[d].v]) + mod) % mod;
            B2 = (sun2[a[d].v] - (ll)(n - siz[a[d].v]) * (n - siz[a[d].v]) % mod + mod) % mod;
            ans = (ans + (ll)f[n - 2] * B1 % mod * A % mod) % mod;
            ans = (ans + (ll)f[n - 4] * B2 % mod * A % mod * A % mod) % mod;
            ans = (ans + (ll)f[n - 4] * (((ll)n * n % mod - 3 * n + 1 + mod) % mod) % mod * B1 % mod * A % mod) % mod;
            ans = (ans - (ll)f[n - 4] * (n - 2 + mod) % mod * B1 % mod * A % mod * A % mod + mod) % mod;
            ans = (ans - (ll)f[n - 4] * (n - 2 + mod) % mod * B2 % mod * A % mod + mod) % mod;
            dfs2(a[d].v, k);
        }
        d = a[d].nxt;
    }
    return;
}
int main()
{
    n = read();
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        u = read();
        v = read();
        ins(u, v);
        ins(v, u);
    }
    f[n - 4] = F(n - 4);
    f[n - 2] = F(n - 2);
    dfs1(1, 0);
    dfs2(1, 0);
    printf("%d", ans);
    return 0;
}