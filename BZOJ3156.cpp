#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const double eps = 1e-8;
int n, pos = 1, top, a[1000005];
ll ans;
struct node
{
    double x;
    double y;
    node(double xx = 0, double yy = 0)
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
    double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    double operator^(const node &bb) const
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
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    l[++top] = line(node(0, 2 * a[n] + (ll)n * n - n), node(1, -2 * n));
    ans = a[n] + (ll)n * (n - 1) / 2;
    for (int i = n - 1; i >= 1; --i)
    {
        while (pos < top && vec[pos].x - i > eps)
            ++pos;
        ll f = (l[pos].b.y * i + l[pos].a.y + 2 * a[i] + (ll)i * i + i) / 2;
        ans = min(ans, f + (ll)i * (i - 1) / 2);
        line now = line(node(0, 2 * f + (ll)i * i - i), node(1, -2 * i));
        while (top > 1 && (now.b ^ (vec[top - 1] - now.a)) > eps)
            --top;
        l[++top] = now;
        if (pos > top)
            pos = top;
        vec[top - 1] = intersect(l[top], l[top - 1]);
    }
    printf("%lld", ans);
    return 0;
}