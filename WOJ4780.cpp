#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, len, ans, a[5000005], b[5000005], c[5000005];
long long cc[5000005];
struct node
{
    long long a;
    int b;
    long long bb;
    int w;
} s[5000005];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
int read()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return x * f;
}
bool cmp(node aa, node bb)
{
    if (aa.a != bb.a)
        return aa.a < bb.a;
    if (aa.b != bb.b)
        return aa.b < bb.b;
    return aa.w < bb.w;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= len)
    {
        c[x] = min(c[x], val);
        x += lowbit(x);
    }
    return;
}
int query(int x)
{
    int num = 0x7f7f7f7f;
    while (x >= 1)
    {
        num = min(c[x], num);
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        s[i].w = i;
        a[i] = read();
        s[i].a = s[i - 1].a + a[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        b[i] = read();
        s[i].bb = s[i - 1].bb + b[i];
        cc[i] = s[i].bb;
    }
    sort(cc + 1, cc + n + 1);
    len = unique(cc + 1, cc + n + 1) - cc - 1;
    for (int i = 1; i <= n; ++i)
        s[i].b = lower_bound(cc + 1, cc + len + 1, s[i].bb) - cc;
    sort(s + 1, s + n + 1, cmp);
    memset(c, 0x7f, sizeof(c));
    for (int i = 1; i <= n; ++i)
    {
        ans = max(ans, s[i].w - query(s[i].b));
        add(s[i].b, s[i].w);
        if (s[i].a >= 0 && s[i].bb >= 0)
            ans = max(ans, s[i].w);
    }
    printf("%d", ans);
    return 0;
}