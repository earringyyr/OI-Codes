#include <iostream>
#include <cstdio>
using namespace std;
int n;
double a[100005], b[100005], c[100005], p[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", &p[i]);
    for (int i = 1; i <= n; ++i)
    {
        a[i] = (a[i - 1] + 1) * p[i];
        b[i] = (b[i - 1] + 2 * a[i - 1] + 1) * p[i];
        c[i] = c[i - 1] + (3 * b[i - 1] + 3 * a[i - 1] + 1) * p[i];
    }
    printf("%.1f", c[n]);
    return 0;
}