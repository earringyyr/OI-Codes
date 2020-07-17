#include <iostream>
#include <cstdio>
using namespace std;
#define dlt 0.000001
int n;
double l, r, a[15];
double check(double k)
{
    double ans = 0, kk = 1;
    for (int i = n + 1; i >= 1; --i)
    {
        ans += a[i] * kk;
        kk *= k;
    }
    return ans;
}
int main()
{
    cin >> n >> l >> r;
    for (int i = 1; i <= n + 1; ++i)
        cin >> a[i];
    double lef = l, rig = r;
    while (rig - lef > dlt)
    {
        double mid1 = lef + (rig - lef) / 3, mid2 = rig - (rig - lef) / 3;
        if (check(mid1) < check(mid2))
            lef = mid1;
        else
            rig = mid2;
    }
    printf("%.5f", lef);
    return 0;
}