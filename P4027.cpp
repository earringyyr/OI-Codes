#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define eps 1e-8
int n, s, q[100005];
double f[100005], g[100005];
struct node
{
    int id;
    double a;
    double b;
    double r;
    double k;
} p[100005], a[100005];
bool cmp(node aa, node bb)
{
    if (aa.k < bb.k)
        return true;
    if (aa.k > bb.k)
        return false;
    if (aa.id < bb.id)
        return true;
    return false;
}
double cross(int u, int v)
{
    return (p[u].r * g[p[u].id] - p[v].r * g[p[v].id]) / (g[p[v].id] - g[p[u].id]);
}
double calc(int u, int v)
{
    return g[p[u].id] * (p[v].k + p[u].r);
}
void cdq(int l, int r)
{
    if (l == r)
    {
        if (f[p[l].id] < f[p[l].id - 1])
        {
            f[p[l].id] = f[p[l].id - 1];
            g[p[l].id] = f[p[l].id] / (p[l].r * p[l].a + p[l].b);
        }
        return;
    }
    int mid = (l + r) >> 1, h = l, t = mid + 1;
    for (int i = l; i <= r; ++i)
        if (p[i].id <= mid)
            a[h++] = p[i];
        else
            a[t++] = p[i];
    for (int i = l; i <= r; ++i)
        p[i] = a[i];
    cdq(l, mid);
    h = 1, t = 0;
    for (int i = l; i <= mid; ++i)
    {
        while (h < t && cross(q[t], i) - cross(q[t - 1], i) < eps)
            --t;
        q[++t] = i;
    }
    for (int i = mid + 1; i <= r; ++i)
    {
        while (h < t && calc(q[h], i) - calc(q[h + 1], i) < eps)
            ++h;
        if (f[p[i].id] < calc(q[h], i) * p[i].a)
        {
            f[p[i].id] = calc(q[h], i) * p[i].a;
            g[p[i].id] = f[p[i].id] / (p[i].r * p[i].a + p[i].b);
        }
    }
    cdq(mid + 1, r);
    h = l;
    t = mid + 1;
    int cnt = l;
    while (h <= mid || t <= r)
        if (t > r || (g[p[h].id] < g[p[t].id] && h <= mid))
            a[cnt++] = p[h++];
        else
            a[cnt++] = p[t++];
    for (int i = l; i <= r; ++i)
        p[i] = a[i];
    return;
}
int main()
{
    scanf("%d%lf", &n, &f[1]);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf%lf", &p[i].a, &p[i].b, &p[i].r);
        p[i].k = p[i].b / p[i].a;
        p[i].id = i;
    }
    g[1] = f[1] / (p[1].r * p[1].a + p[1].b);
    sort(p + 1, p + n + 1, cmp);
    cdq(1, n);
    printf("%.3f", f[n]);
    return 0;
}