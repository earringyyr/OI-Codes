#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, p[300005], h[300005];
struct node
{
    int l;
    int r;
} a[300005];
bool cmp(node aa, node bb)
{
    if (aa.l < bb.l)
        return 1;
    if (aa.l > bb.l)
        return 0;
    if (aa.r < bb.r)
        return 1;
    return 0;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> p[i] >> h[i];
        if (p[i] < h[i])
        {
            cout << -1;
            return 0;
        }
        a[i].l = p[i] - h[i];
        a[i].r = p[i] + h[i];
    }
    sort(a + 1, a + n + 1, cmp);
    int kai, zhong, ma = 0;
    kai = a[1].l;
    zhong = a[1].r;
    for (int i = 2; i <= n; ++i)
    {
        if (a[i].l < zhong)
            zhong = max(a[i].r, zhong);
        else
        {
            ma = max(zhong - kai, ma);
            kai = a[i].l;
            zhong = a[i].r;
        }
    }
    ma = max(zhong - kai, ma);
    printf("%.1f", ma * 1.0 / 2);
    return 0;
}