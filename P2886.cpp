#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, t, s, e, u[105], v[105], w[105];
int sum, c[205];
struct matrix
{
    int a[205][205];
    matrix()
    {
        memset(a, -1, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 1; i <= 200; ++i)
            for (int j = 1; j <= 200; ++j)
                for (int k = 1; k <= 200; ++k)
                    if (a[i][k] != -1 && bb.a[k][j] != -1)
                        if (cc.a[i][j] == -1)
                            cc.a[i][j] = a[i][k] + bb.a[k][j];
                        else
                            cc.a[i][j] = min(cc.a[i][j], a[i][k] + bb.a[k][j]);
        return cc;
    }
};
int main()
{
    scanf("%d%d%d%d", &n, &t, &s, &e);
    c[++sum] = s;
    c[++sum] = e;
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d%d%d", &w[i], &u[i], &v[i]);
        c[++sum] = u[i];
        c[++sum] = v[i];
    }
    sort(c + 1, c + sum + 1);
    int len = unique(c + 1, c + sum + 1) - c - 1;
    s = lower_bound(c + 1, c + len + 1, s) - c;
    e = lower_bound(c + 1, c + len + 1, e) - c;
    for (int i = 1; i <= t; ++i)
    {
        u[i] = lower_bound(c + 1, c + len + 1, u[i]) - c;
        v[i] = lower_bound(c + 1, c + len + 1, v[i]) - c;
    }
    matrix a, b;
    for (int i = 1; i <= t; ++i)
    {
        if (a.a[u[i]][v[i]] == -1)
        {
            a.a[u[i]][v[i]] = w[i];
            a.a[v[i]][u[i]] = w[i];
        }
        else
        {
            a.a[u[i]][v[i]] = min(a.a[u[i]][v[i]], w[i]);
            a.a[v[i]][u[i]] = min(a.a[v[i]][u[i]], w[i]);
        }
    }
    for (int i = 1; i <= 200; ++i)
        b.a[i][i] = 0;
    while (n)
    {
        if (n & 1)
            b = b * a;
        a = a * a;
        n >>= 1;
    }
    printf("%d", b.a[s][e]);
    return 0;
}