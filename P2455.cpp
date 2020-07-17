#include <iostream>
#include <cstdio>
#include <cmath>
#define eps 0.00000001
using namespace std;
int n;
double a[105][105];
bool x = false, y = false;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        int ma = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(abs(a[j][i]) - abs(a[ma][i])) < eps)
            {
                for (int k = i + 1; k <= n; ++k)
                    if (abs(abs(a[j][k]) - abs(a[ma][k])) > eps && abs(a[j][k]) < abs(a[ma][k]))
                    {
                        ma = j;
                        break;
                    }
            }
            else if (abs(a[j][i]) > abs(a[ma][i]))
                ma = j;
        if (ma != i)
            for (int j = i; j <= n + 1; j++)
            {
                double k = a[i][j];
                a[i][j] = a[ma][j];
                a[ma][j] = k;
            }
        if (abs(a[i][i]) < eps)
            continue;
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
        if (abs(a[i][i] < eps))
            if (abs(a[i][n + 1]) > eps)
                x = true;
            else
                y = true;
    if (x)
    {
        printf("-1");
        return 0;
    }
    if (y)
    {
        printf("0");
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        printf("x%d=%.2f\n", i, a[i][n + 1]);
    return 0;
}