#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m, sum;
int num[505], head[505];
int u[150005], v[150005];
double ans, a[505][505], g[150005];
struct node
{
    int v;
    int nxt;
} e[300005];
void ins(int U, int V)
{
    ++sum;
    e[sum].v = V;
    e[sum].nxt = head[U];
    head[U] = sum;
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u[i], &v[i]);
        ++num[u[i]];
        ++num[v[i]];
        ins(u[i], v[i]);
        ins(v[i], u[i]);
    }
    a[1][n] = -1;
    for (int i = 1; i < n; ++i)
    {
        a[i][i] = -1;
        int d = head[i];
        while (d)
        {
            if (e[d].v != n)
                a[i][e[d].v] += 1.0 / num[e[d].v];
            d = e[d].nxt;
        }
    }
    for (int i = 1; i < n; ++i)
    {
        int ma = i;
        for (int j = i + 1; j < n; ++j)
            if (fabs(a[j][i]) > fabs(a[ma][i]))
                ma = j;
        if (ma != i)
            for (int j = i; j <= n; ++j)
                swap(a[i][j], a[ma][j]);
        for (int j = 1; j < n; ++j)
            if (i != j)
            {
                double t = a[j][i] / a[i][i];
                for (int k = i; k <= n; ++k)
                    a[j][k] -= a[i][k] * t;
            }
        double t = a[i][i];
        for (int j = i; j <= n; ++j)
            a[i][j] /= t;
    }
    for (int i = 1; i <= m; ++i)
    {
        if (u[i] != n)
            g[i] += a[u[i]][n] / num[u[i]];
        if (v[i] != n)
            g[i] += a[v[i]][n] / num[v[i]];
    }
    sort(g + 1, g + m + 1);
    for (int i = 1; i <= m; ++i)
        ans += g[i] * (m - i + 1);
    printf("%.3f", ans);
    return 0;
}