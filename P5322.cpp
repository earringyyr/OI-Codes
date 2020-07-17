#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int s, n, m, a[105][105], f[20005];
int main()
{
    scanf("%d%d%d", &s, &n, &m);
    for (int i = 1; i <= s; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[j][i]);
    for (int i = 1; i <= n; ++i)
        sort(a[i] + 1, a[i] + s + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= 1; --j)
            for (int k = 1; k <= s; ++k)
            {
                if (j < 2 * a[i][k] + 1)
                    break;
                f[j] = max(f[j], f[j - 2 * a[i][k] - 1] + i * k);
            }
    printf("%d", f[m]);
    return 0;
}