#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int a[505];
int f[505][505];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        for (int j = i - 1; j >= 1; --j)
        {
            f[j][i] = f[j][i - 1];
            for (int k = j; k < i; ++k)
                if (a[k] == a[i])
                    f[j][i] = max(f[j][i], f[j][k - 1] + f[k + 1][i - 1] + a[i]);
        }
    printf("%d", f[1][n]);
    return 0;
}