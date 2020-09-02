#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int n, top, pos;
int x[1000005], p[1000005], c[1000005], sum[1000005];
int st[1000005], f[1000005];
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
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld%lld", &x[i], &p[i], &c[i]);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + p[i] * x[i];
        p[i] += p[i - 1];
    };
    ++top;
    st[top] = 0;
    l[top] = line(node(0, 0), node(1, 0));
    pos = 1;
    for (int i = 1; i <= n; ++i)
    {
        while (pos < top && vec[pos].x < x[i])
            ++pos;
        f[i] = f[st[pos]] + x[i] * (p[i] - p[st[pos]]) - (sum[i] - sum[st[pos]]) + c[i];
        line now = line(node(0, f[i] + sum[i]), node(1, -p[i]));
        while (top > 1 && (now.b ^ (vec[top - 1] - now.a)) >= 0)
            --top;
        ++top;
        st[top] = i;
        l[top] = now;
        vec[top - 1] = intersect(l[top], l[top - 1]);
        if (top < pos)
            pos = top;
    }
    printf("%lld", f[n]);
    return 0;
}