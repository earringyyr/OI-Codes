#include <iostream>
#include <cstdio>
using namespace std;
int n;
double a[10005], f[10005];
int main()
{
    scanf("%d", &n);
    for (int i = n - 1; i >= 0; --i)
    {
        a[i] = a[i + 1] + (double)n / (n - i);
        f[i] = (double)i / (n - i) * (2 * a[i] + 1) + f[i + 1] + 2 * a[i + 1] + 1;
    }
    printf("%.2f", (a[0] + f[0]) / 2);
    return 0;
}