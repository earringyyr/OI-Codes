#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-8;
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
        int id = i;
        for (int j = i + 1; j <= n; ++j)
            if (fabs(a[j][i]) > fabs(a[id][i]))
                id = j;
        if (i != id)
            for (int j = i; j <= n + 1; ++j)
                swap(a[i][j], a[id][j]);
        if (fabs(a[i][i]) < eps)
        {
            printf("No Solution");
            return 0;
        }
        for (int j = 1; j <= n; ++j)
            if (i != j)
            {
                double t = a[j][i] / a[i][i];
                for (int k = i; k <= n + 1; ++k)
                    a[j][k] -= t * a[i][k];
            }
        double t = a[i][i];
        for (int j = i + 1; j <= n + 1; ++j)
            a[i][j] /= t;
    }
    for (int i = 1; i <= n; ++i)
        printf("%.2f\n", a[i][n + 1]);
    return 0;
}