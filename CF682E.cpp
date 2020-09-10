#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, S, top, minx = 1, maxn;
struct node
{
    int x;
    int y;
    node(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
    node operator+(const node &bb) const
    {
        return node(x + bb.x, y + bb.y);
    }
    node operator-(const node &bb) const
    {
        return node(x - bb.x, y - bb.y);
    }
    int operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
    int dis(node bb)
    {
        return (x - bb.x) * (x - bb.x) + (y - bb.y) * (y - bb.y);
    }
} p[5005], st[50005], A, B, C;
bool cmp(node aa, node bb)
{
    if (((aa - p[1]) ^ (bb - p[1])) == 0)
        return aa.dis(p[1]) < bb.dis(p[1]);
    return ((aa - p[1]) ^ (bb - p[1])) > 0;
}
bool check(node aa, node bb, node cc, node dd)
{
    int sa = abs((cc - aa) ^ (cc - bb));
    int sb = abs((dd - aa) ^ (dd - bb));
    return sa < sb;
}
signed main()
{
    scanf("%lld%lld", &n, &S);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        if (p[i].x == p[minx].x && p[i].y < p[minx].y)
            minx = i;
        if (p[i].x < p[minx].x)
            minx = i;
    }
    swap(p[1], p[minx]);
    sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
    {
        while (top >= 2 && ((p[i] - st[top - 1]) ^ (st[top] - st[top - 1])) >= 0)
            --top;
        st[++top] = p[i];
    }
    n = top;
    for (int i = 1; i <= n; ++i)
    {
        int k = (i + 2) % n;
        if (!k)
            k = n;
        for (int j = i + 1; j != i; j = (j + 1) % n ? (j + 1) % n : n)
        {
            while (k != i && check(st[i], st[j], st[k], st[(k + 1) % n ? (k + 1) % n : n]))
                k = (k + 1) % n ? (k + 1) % n : n;
            if (abs((st[i] - st[j]) ^ (st[j] - st[k])) > maxn)
            {
                maxn = abs((st[i] - st[j]) ^ (st[j] - st[k]));
                A = st[i];
                B = st[j];
                C = st[k];
            }
        }
    }
    printf("%lld %lld\n", (A + B - C).x, (A + B - C).y);
    printf("%lld %lld\n", (B + C - A).x, (B + C - A).y);
    printf("%lld %lld\n", (C + A - B).x, (C + A - B).y);
    return 0;
}