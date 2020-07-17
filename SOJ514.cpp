#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n;
double a[105][105];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; ++i)
    {
        int ma = i;
        for (int j = i + 1; j <= n; ++j)
            if (abs(a[j][i]) > abs(a[ma][i]))
                ma = j;
        for (int j = i; j <= n + 1; ++j)
            swap(a[i][j], a[ma][j]);
        for (int j = 1; j <= n; ++j)
            if (i != j)
            {
                double t = a[j][i] / a[i][i];
                for (int k = i; k <= n + 1; ++k)
                    a[j][k] -= a[i][k] * t;
            }
        double t = a[i][i];
        for (int j = i; j <= n + 1; ++j)
            a[i][j] /= t;
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", (int)(a[i][n + 1] + 0.5));
    return 0;
}