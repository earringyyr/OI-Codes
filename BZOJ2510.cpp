#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k, a[1005];
double ans[1005];
struct node
{
    double a[1005];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator*(const node &bb) const
    {
        node cc;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                cc.a[i] += a[j] * bb.a[i - j + 1 > 0 ? i - j + 1 : n + (i - j + 1)];
        return cc;
    }
};
node ksm(node aa)
{
    node bb;
    bb.a[1] = 1;
    while (k)
    {
        if (k & 1)
            bb = bb * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return bb;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    node aa;
    aa.a[1] = 1 - 1.0 / m;
    aa.a[n] = 1.0 / m;
    aa = ksm(aa);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ans[i] += aa.a[j - i + 1 > 0 ? j - i + 1 : n + (j - i + 1)] * a[j];
    for (int i = 1; i <= n; ++i)
        printf("%.3f\n", ans[i]);
    return 0;
}