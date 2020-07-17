#include <iostream>
#include <cstdio>
using namespace std;
int n, A, B, C, a[20000005];
double num;
int main()
{
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    for (int i = 2; i <= n; ++i)
        a[i] = ((long long)a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; ++i)
        a[i] = a[i] % C + 1;
    a[0] = a[n];
    for (int i = 1; i <= n; ++i)
        if (a[i] > a[i - 1])
            num += 1.0 / a[i];
        else
            num += 1.0 / a[i - 1];
    printf("%.3f", num);
    return 0;
}