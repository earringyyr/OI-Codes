#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n;
double l, r, a[15];
int main()
{
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = n; i >= 0; --i)
        scanf("%lf", &a[i]);
    while (r - l > eps)
    {
        double mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
        double num1 = 1, num2 = 1, ans1 = 0, ans2 = 0;
        for (int i = 0; i <= n; ++i)
        {
            ans1 += a[i] * num1;
            ans2 += a[i] * num2;
            num1 *= mid1;
            num2 *= mid2;
        }
        if (ans1 > ans2)
            r = mid2;
        else
            l = mid1;
    }
    printf("%.5f", l);
    return 0;
}