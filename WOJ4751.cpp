#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = 400010, E = 2000000;
int n, s, m, i, x, y, z, tot, l[N << 1], r[N << 1], pos[N];
int a[M], d[M], g[M], v[E], nxt[E], ed;
char w[E];
int h, t, q[M], f[M];
inline void read(int &a)
{
    char c;
    while (!(((c = getchar()) >= '0') && (c <= '9')))
        ;
    a = c - '0';
    while (((c = getchar()) >= '0') && (c <= '9'))
        (a *= 10) += c - '0';
}
inline void add(int x, int y, char z)
{
    d[y]++;
    v[++ed] = y;
    w[ed] = z;
    nxt[ed] = g[x];
    g[x] = ed;
}
inline int build(int a, int b)
{
    int x = ++tot;
    if (a == b)
        return pos[a] = x;
    int mid = (a + b) >> 1;
    add(l[x] = build(a, mid), x, 0);
    add(r[x] = build(mid + 1, b), x, 0);
    return x;
}
void ask(int x, int a, int b, int c, int d)
{
    if (c > d)
        return;
    if (c <= a && b <= d)
    {
        add(x, tot, 1);
        return;
    }
    int mid = (a + b) >> 1;
    if (c <= mid)
        ask(l[x], a, mid, c, d);
    if (d > mid)
        ask(r[x], mid + 1, b, c, d);
}
int main()
{
    read(n), read(s), read(m);
    build(1, n);
    while (s--)
        read(x), read(y), a[pos[x]] = y;
    while (m--)
    {
        read(x), read(y), read(z);
        tot++;
        for (i = 1; i <= z; i++)
            read(q[i]), add(tot, pos[q[i]], 0);
        ask(1, 1, n, x, q[1] - 1);
        ask(1, 1, n, q[z] + 1, y);
        for (i = 1; i < z; i++)
            ask(1, 1, n, q[i] + 1, q[i + 1] - 1);
    }
    for (h = i = 1; i <= tot; i++)
        if (!d[i])
            f[q[++t] = i] = 1;
    while (h <= t)
    {
        x = q[h++];
        if (f[x] > 1000000000)
            return puts("Impossible"), 0;
        if (a[x])
        {
            if (a[x] < f[x])
                return puts("Impossible"), 0;
            if (a[x] > f[x])
                f[x] = a[x];
        }
        for (i = g[x]; i; i = nxt[i])
        {
            if (f[v[i]] < f[x] + w[i])
                f[v[i]] = f[x] + w[i];
            if (!(--d[v[i]]))
                q[++t] = v[i];
        }
    }
    if (t < tot)
        return puts("Impossible"), 0;
    for (puts("Possible"), i = 1; i <= n; i++)
        printf("%d ", f[pos[i]]);
    return 0;
}