#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, a, b, c, top, pos = 1;
int x[1000005], f[1000005];
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
    int operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} vec[1000005];
struct line
{
    node a;
    node b;
    line() {}
    line(node aa, node bb)
    {
        a = aa;
        b = bb;
    }
} l[1000005];
node intersect(line aa, line bb)
{
    node cc = aa.a - bb.a;
    double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    cc = node(aa.b.x * k, aa.b.y * k);
    return aa.a + cc;
}
signed main()
{
    scanf("%lld", &n);
    scanf("%lld%lld%lld", &a, &b, &c);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &x[i]);
        x[i] += x[i - 1];
    }
    l[++top] = line(node(0, 0), node(1, 0));
    for (int i = 1; i <= n; ++i)
    {
        while (pos < top && vec[pos].x < x[i])
            ++pos;
        f[i] = l[pos].b.y * x[i] + l[pos].a.y + a * x[i] * x[i] + b * x[i] + c;
        line now = line(node(0, f[i] + a * x[i] * x[i] - b * x[i]), node(1, -2 * a * x[i]));
        while (top > 1 && ((vec[top - 1] - now.a) ^ now.b) >= 0)
            --top;
        l[++top] = now;
        vec[top - 1] = intersect(l[top - 1], l[top]);
        if (pos > top)
            pos = top;
    }
    printf("%lld", f[n]);
    return 0;
}