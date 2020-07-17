#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, p, xx, yy, cnt, a[2505];
long long ans;
struct node
{
    int a;
    int b;
    int num;
} s[2505];
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;
inline int read()
{
    int x = 0;
    char c = gc();
    while (!isdigit(c))
        c = gc();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = gc();
    }
    return x;
}
inline bool cmp(node aa, node bb)
{
    if (aa.a != bb.a)
        return aa.a < bb.a;
    return aa.b < bb.b;
}
inline void exgcd(int a, int b)
{
    if (b == 0)
    {
        xx = 1;
        yy = 0;
        return;
    }
    exgcd(b, a % b);
    int tmp = xx;
    xx = yy;
    yy = tmp - a / b * yy;
    return;
}
int main()
{
    n = read();
    p = read();
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    sort(a + 1, a + n + 1);
    for (register int i = 1; i <= n; ++i)
        if (a[i] != a[i - 1])
        {
            ++cnt;
            s[cnt].a = a[i] % p;
            s[cnt].b = a[i];
            s[cnt].num = 1;
        }
        else
            ++s[cnt].num;
    sort(s + 1, s + cnt + 1, cmp);
    for (register int i = 1; i <= n; ++i)
    {
        --s[i].num;
        for (register int j = i; j <= n; ++j)
        {
            if (s[j].num <= 0)
                continue;
            --s[j].num;
            exgcd((long long)s[i].a * s[j].a % p, p);
            int k = (xx % p + p) % p;
            int l = j, r = cnt;
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (k > s[mid].a)
                    l = mid + 1;
                else
                    r = mid;
            }
            int x = l;
            l = j;
            r = cnt;
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (k < s[mid].a)
                    r = mid - 1;
                else
                    l = mid;
            }
            int y = l;
            if (s[x].a != k)
            {
                ++s[j].num;
                continue;
            }
            if (s[x].num <= 0)
                ++x;
            ans += y - x + 1;
            ++s[j].num;
        }
        ++s[i].num;
    }
    printf("%lld", ans);
    return 0;
}