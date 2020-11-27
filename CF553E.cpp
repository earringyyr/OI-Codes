#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
const double pi = acos(-1.0), inf = 1e9;
int n, m, t, x, sum, hh, tt = 1, num = 1;
int head[55], in[55], dis[55], vis[55];
int l[2505];
int r[120005];
int p[105][20005];
double dp[55][40005];
char buf[1 << 21], *p1 = buf, *p2 = buf;
struct node
{
    int id;
    int v;
    int w;
    int nxt;
} a[105];
struct complex
{
    double x;
    double y;
    complex(double a = 0, double b = 0)
    {
        x = a;
        y = b;
    }
    complex operator+(complex a)
    {
        return complex(x + a.x, y + a.y);
    }
    complex operator-(complex a)
    {
        return complex(x - a.x, y - a.y);
    }
    complex operator*(complex a)
    {
        return complex(x * a.x - y * a.y, x * a.y + y * a.x);
    }
} f[120005], g[105][120005];
int read()
{
    int x = 0;
    char ch = gc();
    while (!isdigit(ch))
        ch = gc();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = gc();
    }
    return x;
}
void ins(int id, int u, int v, int w)
{
    ++sum;
    a[sum].id = id;
    a[sum].v = v;
    a[sum].w = w;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void fft(complex *c, int type)
{
    for (int i = 0; i < num; ++i)
        if (i < r[i])
            swap(c[i], c[r[i]]);
    for (int mid = 1; mid < num; mid <<= 1)
    {
        complex w(cos(pi / mid), type * sin(pi / mid));
        for (int j = 0; j < num; j += (mid << 1))
        {
            complex ww(1, 0);
            for (int k = 0; k < mid; ++k)
            {
                complex x = c[j + k], y = ww * c[j + mid + k];
                c[j + k] = x + y;
                c[j + mid + k] = x - y;
                ww = w * ww;
            }
        }
    }
    if (type == -1)
        for (int i = 0; i < num; ++i)
            c[i].x /= num;
    return;
}
int main()
{
    n = read();
    m = read();
    t = read();
    x = read();
    for (int i = 1; i < n; ++i)
    {
        dis[i] = inf;
        for (int j = 0; j <= 2 * t; ++j)
            dp[i][j] = inf;
    }
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        u = read();
        v = read();
        w = read();
        ins(i, v, u, w);
        ++in[u];
        for (int j = 1; j <= t; ++j)
            p[i][j] = read();
    }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int d = head[j];
            while (d)
            {
                dis[a[d].v] = min(dis[a[d].v], dis[j] + a[d].w);
                d = a[d].nxt;
            }
        }
    while (num < 3 * t)
        num <<= 1;
    for (int i = 0; i < num; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? num >> 1 : 0);
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 0; j < t; ++j)
            g[i][j].x = p[i][t - j];
        fft(g[i], 1);
    }
    l[1] = n;
    vis[n] = 1;
    while (hh < tt)
    {
        int k = l[++hh];
        vis[k] = 0;
        for (int j = t + 1; j <= 2 * t; ++j)
            dp[k][j] = dis[k] + x;
        int d = head[k];
        while (d)
        {
            for (int j = 0; j <= 2 * t; ++j)
            {
                f[j].x = dp[k][j];
                f[j].y = 0;
            }
            for (int j = 2 * t + 1; j < num; ++j)
            {
                f[j].x = 0;
                f[j].y = 0;
            }
            fft(f, 1);
            for (int j = 0; j < num; ++j)
                f[j] = f[j] * g[a[d].id][j];
            fft(f, -1);
            int flg = 0;
            for (int j = 0; j <= t; ++j)
            {
                double tmp = f[t + j].x / 100000 + a[d].w;
                if (tmp < dp[a[d].v][j])
                {
                    dp[a[d].v][j] = tmp;
                    flg = 1;
                }
            }
            if (flg && !vis[a[d].v])
            {
                vis[a[d].v] = 1;
                l[++tt] = a[d].v;
            }
            d = a[d].nxt;
        }
    }
    printf("%.10f", dp[1][0]);
    return 0;
}