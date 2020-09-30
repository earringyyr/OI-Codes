#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int eps = 1e-8;
int n, sum, ans = 1, x[205], y[205];
double k[40005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
        for (int j = 1; j < i; ++j)
            if (x[i] != x[j])
                k[++sum] = (double)(y[i] - y[j]) / (x[i] - x[j]);
            else
                k[++sum] = 1e14;
    }
    sort(k + 1, k + sum + 1);
    for (int i = 2; i <= sum; ++i)
        if (fabs(k[i] - k[i - 1]) > eps)
            ++ans;
    printf("%d", ans);
    return 0;
}