#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define eps 1e-8
using namespace std;
int n, sum, head = 1, tail;
double ans = 0;
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
} p[55], vec[1005];
struct line
{
    node a;
    node b;
    double k;
    line()
    {
    }
    line(node aa, node bb)
    {
        a = aa;
        b = bb - aa;
        k = atan2(b.y, b.x);
    }
} s[1005], st[1005];
bool cmp(line aa, line bb)
{
    return aa.k < bb.k;
}
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
    {
        int m;
        scanf("%d", &m);
        for (int j = 1; j <= m; ++j)
            scanf("%lf%lf", &p[j].x, &p[j].y);
        p[m + 1] = p[1];
        for (int j = 1; j <= m; ++j)
            s[++sum] = line(p[j], p[j + 1]);
    }
    sort(s + 1, s + sum + 1, cmp);
    st[++tail] = s[1];
    for (int i = 2; i <= sum; ++i)
    {
        while (head < tail && (s[i].b ^ (vec[tail - 1] - s[i].a)) < eps)
            --tail;
        while (head < tail && (s[i].b ^ (vec[head] - s[i].a)) < eps)
            ++head;
        st[++tail] = s[i];
        if (fabs(st[tail].b ^ st[tail - 1].b) < eps)
        {
            --tail;
            if (((s[i].a - st[tail].a) ^ st[tail].b) < eps)
                st[tail] = s[i];
        }
        if (head < tail)
            vec[tail - 1] = intersect(st[tail - 1], st[tail]);
    }
    while (head < tail && (st[head].b ^ (vec[tail - 1] - st[head].a)) < eps)
        --tail;
    if (head < tail)
        vec[tail] = intersect(st[head], st[tail]);
    vec[tail + 1] = vec[head];
    for (int i = head; i <= tail; ++i)
        ans += (vec[i] ^ vec[i + 1]);
    printf("%.3f", ans / 2);
    return 0;
}