#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int n, q, cnt, len, num, a[50005], b[50005], c[50005], ans[50005];
struct node
{
    int id;
    int l;
    int r;
} s[50005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
bool cmp(node aa, node bb)
{
    if ((aa.l - 1) / len == (bb.l - 1) / len)
    {
        if (aa.r != bb.r)
            if ((aa.l - 1) / len % 2 == 0)
                return aa.r < bb.r;
            else
                return aa.r > bb.r;
        return aa.l < bb.l;
    }
    else
        return aa.l < bb.l;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int k, int val)
{
    for (int i = k; i <= cnt; i += lowbit(i))
        c[i] += val;
    return;
}
int ask(int k)
{
    int ans = 0;
    for (int i = k; i >= 1; i -= lowbit(i))
        ans += c[i];
    return ans;
}
void add(int k)
{
    add(a[k], 1);
    return;
}
void del(int k)
{
    add(a[k], -1);
    return;
}
int main()
{
    n = read();
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    q = read();
    for (int i = 1; i <= q; ++i)
    {
        s[i].id = i;
        s[i].l = read();
        s[i].r = read();
    }
    sort(s + 1, s + q + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= q; ++i)
    {
        while (l < s[i].l)
        {
            num -= ask(a[l] - 1);
            del(l++);
        }
        while (l > s[i].l)
        {
            add(--l);
            num += ask(a[l] - 1);
        }
        while (r < s[i].r)
        {
            add(++r);
            num += ask(cnt) - ask(a[r]);
        }
        while (r > s[i].r)
        {
            num -= ask(cnt) - ask(a[r]);
            del(r--);
        }
        ans[s[i].id] = num;
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}