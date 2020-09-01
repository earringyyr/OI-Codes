#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int K, n, p[20], s[20];
double ans, f[105][40005];
int main()
{
    scanf("%d%d", &K, &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        int tmp;
        while (scanf("%d", &tmp))
        {
            if (!tmp)
                break;
            s[i] |= (1 << (tmp - 1));
        }
    }
    for (int i = K; i >= 1; --i)
        for (int j = 0; j < (1 << n); ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                if ((j & s[k]) == s[k])
                    f[i][j] += max(f[i + 1][j], f[i + 1][j | (1 << (k - 1))] + p[k]);
                else
                    f[i][j] += f[i + 1][j];
            }
            f[i][j] /= n;
        }
    printf("%.6f", f[1][0]);
    return 0;
}