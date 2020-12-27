#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef __int128 ll;
int n, m, sum, hh, tt;
int d[100005], head[100005];
int l[100005], in[100005];
ll p[100005], q[100005];
struct node
{
    int v;
    int nxt;
} a[500005];
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
void write(ll x)
{
    if (x >= 10)
        write(x / 10);
    putchar((x % 10) + '0');
    return;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i)
    {
        d[i] = read();
        for (int j = 1; j <= d[i]; ++j)
        {
            int v;
            v = read();
            ins(i, v);
            ++in[v];
        }
    }
    for (int i = 1; i <= n; ++i)
        q[i] = 1;
    for (int i = 1; i <= m; ++i)
        p[i] = 1;
    for (int i = 1; i <= n; ++i)
        if (!in[i])
            l[++tt] = i;
    while (hh < tt)
    {
        int k = l[++hh];
        int d = head[k];
        while (d)
        {
            --in[a[d].v];
            if (!in[a[d].v])
                l[++tt] = a[d].v;
            d = a[d].nxt;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int k = l[i];
        if (d[k])
        {
            ll P = p[k], Q = q[k];
            ll GCD = gcd(P, d[k]);
            P = P / GCD;
            Q = d[k] / GCD * Q;
            int d = head[k];
            while (d)
            {
                GCD = gcd(Q, q[a[d].v]);
                p[a[d].v] = P * (q[a[d].v] / GCD) + p[a[d].v] * (Q / GCD);
                q[a[d].v] = Q / GCD * q[a[d].v];
                GCD = gcd(p[a[d].v], q[a[d].v]);
                p[a[d].v] /= GCD;
                q[a[d].v] /= GCD;
                d = a[d].nxt;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!d[i])
        {
            write(p[i]);
            putchar(' ');
            write(q[i]);
            putchar('\n');
        }
    return 0;
}