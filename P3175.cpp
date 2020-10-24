#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int n, num[2000005];
double ans, p[2000005];
int lowbit(int x)
{
    return x & -x;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); ++i)
    {
        scanf("%lf", &p[i]);
        if (i)
            num[i] = num[i - lowbit(i)] + 1;
    }
    for (int mid = 1; mid < (1 << n); mid <<= 1)
        for (int j = 0; j < (1 << n); j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                double x = p[j + k], y = p[j + mid + k];
                p[j + k] = x;
                p[j + mid + k] = x + y;
            }
    for (int i = 1; i < (1 << n); ++i)
    {
        if ((1 - p[((1 << n) - 1) ^ i]) < eps)
        {
            printf("INF");
            return 0;
        }
        if (num[i] % 2 == 0)
            ans -= 1.0 / (1.0 - p[((1 << n) - 1) ^ i]);
        else
            ans += 1.0 / (1.0 - p[((1 << n) - 1) ^ i]);
    }
    printf("%.10f", ans);
    return 0;
}