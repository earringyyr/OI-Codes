#include <iostream>
#include <cstdio>
#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, mod;
int f[350005];
int Mod(int x)
{
    return x > mod ? x - mod : x;
}
int main()
{
    scanf("%d%d", &n, &mod);
    m = n / 2;
    f[0] = 1;
    for (int i = 1; i <= n - 1; ++i)
        f[i] = Mod(f[i - 1] + (i > m ? mod - 2 : 0));
    for (int T = 1; T <= 2; ++T)
        for (int i = 1; i <= n - 1; ++i)
            for (int j = 1; j * (3 * j - 1) / 2 <= i; ++j)
            {
                int k;
                k = j * (3 * j - 1) / 2;
                if (k > i)
                    break;
                if (j & 1)
                    f[i] = Mod(f[i] + f[i - k]);
                else
                    f[i] = Mod(f[i] - f[i - k] + mod);
                k = j * (3 * j + 1) / 2;
                if (k > i)
                    break;
                if (j & 1)
                    f[i] = Mod(f[i] + f[i - k]);
                else
                    f[i] = Mod(f[i] - f[i - k] + mod);
            }
    if (n & 1)
        f[n - 1] = Mod(f[n - 1] + f[n - m - 2]);
    printf("%d", f[n - 1]);
    return 0;
}