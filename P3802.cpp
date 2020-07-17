#include <iostream>
#include <cstdio>
using namespace std;
double a[8], sum;
double ans;
int main()
{
    for (int i = 1; i <= 7; ++i)
    {
        scanf("%lf", &a[i]);
        sum += a[i];
    }
    if (sum < 7)
    {
        puts("0.000");
        return 0;
    }
    ans = 5040 * (sum - 6);
    for (int i = 1; i <= 7; ++i)
        ans = ans * a[i] / (sum - i + 1);
    printf("%.3f", ans);
    return 0;
}