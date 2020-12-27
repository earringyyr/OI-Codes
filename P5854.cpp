#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
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
typedef long long ll;
int n, top;
int p[10000005], st[10000005];
int lch[10000005], rch[10000005];
ll ans[2];
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        p[i] = read();
        while (top && p[st[top]] > p[i])
            --top;
        lch[i] = rch[st[top]];
        rch[st[top]] = i;
        st[++top] = i;
    }
    for (int i = 1; i <= n; ++i)
    {
        ans[0] ^= (ll)i * (lch[i] + 1);
        ans[1] ^= (ll)i * (rch[i] + 1);
    }
    printf("%lld %lld", ans[0], ans[1]);
    return 0;
}