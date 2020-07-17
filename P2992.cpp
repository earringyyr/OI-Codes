#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long n;
long long ans, num;
struct node
{
    long long x;
    long long y;
} a[200005];
long long jiao(node aa, node bb, node cc)
{
    return (aa.x - cc.x) * (bb.y - cc.y) - (bb.x - cc.x) * (aa.y - cc.y);
}
long long ju(node aa, node bb, node cc)
{
    return ((aa.x - cc.x) * (aa.x - cc.x) + (aa.y - cc.y) * (aa.y - cc.y)) - ((bb.x - cc.x) * (bb.x - cc.x) + (bb.y - cc.y) * (bb.y - cc.y));
}
bool cmp(node aa, node bb)
{
    return atan2(aa.y, aa.x) < atan2(bb.y, bb.x);
}
int main()
{
    cin >> n;
    a[0].x = 0;
    a[0].y = 0;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].x >> a[i].y;
    if (n == 1 || n == 2)
    {
        cout << 0;
        return 0;
    }
    ans = n * (n - 1) * (n - 2) / 6;
    sort(a + 1, a + n + 1, cmp);
    for (int i = n + 1; i <= 2 * n; ++i)
        a[i] = a[i - n];
    long long l = 1, r = 1;
    for (l = 1; l <= n; ++l)
    {
        while (r + 1 < l + n && jiao(a[r + 1], a[0], a[l]) > 0)
            ++r;
        if (r > l)
            ans -= (r - l) * (r - l - 1) / 2;
    }
    printf("%lld", ans);
    return 0;
}