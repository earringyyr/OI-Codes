#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
using namespace std;
int n, q, s, t;
ll f[1005][1005];
struct node
{
    int a;
    int b;
    node(int aa = 0, int bb = 0)
    {
        a = aa;
        b = bb;
    }
} a[1005], b[1005];
bool cmp1(node aa, node bb)
{
    return aa.a < bb.a;
}
bool cmp2(node aa, node bb)
{
    return aa.b > bb.b;
}
int main()
{
    memset(f, 0x7f, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int aa, bb;
        scanf("%d%d", &aa, &bb);
        if (aa <= bb)
            a[++s] = node(aa, bb);
        else
            b[++t] = node(aa, bb);
    }
    sort(a + 1, a + s + 1, cmp1);
    sort(b + 1, b + t + 1, cmp2);
    f[t + 1][0] = 0;
    for (int i = t; i >= 1; --i)
    {
        f[i][0] = 0;
        for (int j = 1; j <= t - i + 1; ++j)
            f[i][j] = min(f[i + 1][j], max((ll)b[i].a + 1, b[i].a - b[i].b + f[i + 1][j - 1]));
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int num = 0;
        ll c;
        scanf("%lld", &c);
        for (int j = 1; j <= s; ++j)
            if (c > a[j].a)
            {
                c -= a[j].a;
                c += a[j].b;
                ++num;
            }
        for (int j = t; j >= 0; --j)
            if (f[1][j] <= c)
            {
                printf("%d\n", num + j);
                break;
            }
    }
    return 0;
}