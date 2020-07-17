#include <iostream>
#include <cstdio>
using namespace std;
int n, a[1 << 17], b[1 << 17];
int main()
{
    n = 1 << 17;
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &b[i]);
    for (int i = 0; i < n; ++i)
    {
        int c = 0;
        for (int j = 0; j <= i; ++j)
            c = max(c, a[j] + b[i - j]);
        printf("%d ", c);
    }
    return 0;
}