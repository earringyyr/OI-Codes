#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const long double eps = 1e-18, inf = 1e12;
int n, sum, num, head, tail;
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
struct node
{
    long double x;
    long double y;
    node(long double xx = 0, long double yy = 0)
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
    long double operator*(const node &bb) const
    {
        return x * bb.x + y * bb.y;
    }
    long double operator^(const node &bb) const
    {
        return x * bb.y - y * bb.x;
    }
} vec[200005];
struct line
{
    int id;
    node a;
    node b;
    long double k;
    line()
    {
    }
    line(node aa, node bb, int cc = 0)
    {
        id = cc;
        a = aa;
        b = bb;
        k = atan2(b.y, b.x);
    }
} s[200005], st[200005], p[200005];
bool cmp(line aa, line bb)
{
    if (fabs(aa.k - bb.k) > eps)
        return aa.k < bb.k;
    else
        return (aa.b ^ bb.b) > 0;
}
node intersect(line aa, line bb)
{
    node cc = aa.a - bb.a;
    long double k = (bb.b ^ cc) / (aa.b ^ bb.b);
    cc = node(aa.b.x * k, aa.b.y * k);
    return aa.a + cc;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        long double x, y, yy;
        x = read();
        y = read() * 5;
        yy = read() * 5;
        p[++num] = line(node(0, y / x), node(1, -x), i);
        p[++num] = line(node(0, yy / x), node(-1, x), i);
    }
    p[++num] = line(node(0, 0), node(1, 0));
    p[++num] = line(node(0, inf), node(-1, 0));
    p[++num] = line(node(inf, 0), node(0, 1));
    p[++num] = line(node(-inf, 0), node(0, -1));
    sort(p + 1, p + num + 1, cmp);
    int l = 1, r = n;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        sum = 0;
        head = 1;
        tail = 0;
        for (int i = 1; i <= num; ++i)
            if (p[i].id <= mid)
                s[++sum] = p[i];
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
        if (head == tail)
            r = mid - 1;
        else
        {
            vec[tail] = intersect(st[head], st[tail]);
            int p = 0;
            for (int i = head; i <= tail; ++i)
                if (vec[i].x < eps)
                {
                    p = 1;
                    break;
                }
            if (p)
                l = mid;
            else
                r = mid - 1;
        }
    }
    printf("%d", l);
    return 0;
}