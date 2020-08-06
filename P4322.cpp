#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-4;
int k, n, sum;
int s[2505], p[2505], head[2505], siz[2505];
double f[2505][2505];
struct node
{
    int v;
    int nxt;
} a[2505];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int id, int fa, double mid)
{
    siz[id] = 1;
    f[id][1] = p[id] - s[id] * mid;
    for (int i = 2; i <= k + 1; ++i)
        f[id][i] = -250000000000;
    int d = head[id];
    while (d)
    {
        dfs(a[d].v, id, mid);
        for (int i = min(siz[id] + siz[a[d].v], k + 1); i >= 1; --i)
            for (int j = max(1, i - siz[id]); j <= min(siz[a[d].v], i - 1); ++j)
                f[id][i] = max(f[id][i], f[id][i - j] + f[a[d].v][j]);
        siz[id] += siz[a[d].v];
        d = a[d].nxt;
    }
    return;
}
int main()
{
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; ++i)
    {
        int r;
        scanf("%d%d%d", &s[i], &p[i], &r);
        ins(r, i);
    }
    double l = 0, r = 10000;
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        dfs(0, 0, mid);
        if (f[0][k + 1] >= 0)
            l = mid;
        else
            r = mid;
    }
    printf("%.3f", l);
    return 0;
}