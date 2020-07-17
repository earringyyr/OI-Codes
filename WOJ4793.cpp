#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int n, m, mm, ans1, ans2;
struct node
{
    int val;
    int num;
} a[1000005], b[1000005], c[1000005], aa[1000005], bb[1000005], cc[1000005];
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
bool cmp(node aa, node bb)
{
    return aa.val < bb.val;
}
signed main()
{
    n = read(), m = read(), mm = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i].val = read();
        a[i].num = read();
    }
    for (int i = 1; i <= m; ++i)
    {
        b[i].val = read();
        b[i].num = read();
    }
    for (int i = 1; i <= mm; ++i)
    {
        c[i].val = read();
        c[i].num = read();
    }
    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + m + 1, cmp);
    sort(c + 1, c + mm + 1, cmp);
    for (int i = 1; i <= n; ++i)
        aa[i] = a[i];
    for (int i = 1; i <= m; ++i)
        bb[i] = b[i];
    for (int i = 1; i <= mm; ++i)
        cc[i] = c[i];
    int j = n;
    for (int i = 1; i <= mm; ++i)
    {
        while (j && a[j].val >= c[i].val && a[j].num < c[i].num)
        {
            ans1 += a[j].num * (a[j].val - c[i].val);
            c[i].num -= a[j].num;
            a[j].num = 0;
            --j;
        }
        if (!j || a[j].val < c[i].val)
            break;
        ans1 += c[i].num * (a[j].val - c[i].val);
        a[j].num -= c[i].num;
        c[i].num = 0;
    }
    swap(a, aa);
    swap(b, bb);
    swap(c, cc);
    int pan = 0;
    j = 1;
    for (int i = 1; i <= m; ++i)
    {
        while (j < n && a[j].val < b[i].val)
            ++j;
        while (j < n && a[j].val >= b[i].val && a[j].num < b[i].num)
        {
            b[i].num -= a[j].num;
            a[j].num = 0;
            ++j;
        }
        if (a[j].num < b[i].num)
        {
            pan = 1;
            break;
        }
        a[j].num -= b[i].num;
        b[i].num = 0;
        if (j == n && !a[j].num)
        {
            pan = 1;
            break;
        }
    }
    j = n;
    for (int i = 1; i <= mm; ++i)
    {
        if (c[i].val >= 0)
            break;
        while (j && a[j].val >= c[i].val && a[j].num < c[i].num)
        {
            ans2 += a[j].num * (a[j].val - c[i].val);
            c[i].num -= a[j].num;
            a[j].num = 0;
            --j;
        }
        if (!j || a[j].val < c[i].val)
            break;
        ans2 += c[i].num * (a[j].val - c[i].val);
        a[j].num -= c[i].num;
        c[i].num = 0;
    }
    if (!pan)
        for (int i = 1; i <= n; ++i)
            if (a[i].val > 0)
                ans2 += a[i].val * a[i].num;
    printf("%lld", max(ans1, ans2));
    return 0;
}