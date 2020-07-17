#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, ans, a[200005], pw[200005], f[200005][2][2][2];
int main()
{
    scanf("%d", &n);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        pw[i] = (ll)2 * pw[i - 1] % mod;
    }
    f[0][0][0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int x = 0; x < 2; ++x)
            for (int y = 0; y < 2; ++y)
                for (int z = 0; z < 2; ++z)
                {
                    if (a[i] != 1)
                    {
                        if (y)
                        {
                            f[i][x][y][z] = (f[i][x][y][z] + (ll)f[i - 1][x][y][z] * pw[i - 2] % mod) % mod;
                            f[i][x | 1][y][z ^ 1] = (f[i][x | 1][y][z ^ 1] + (ll)f[i - 1][x][y][z] * pw[i - 2] % mod) % mod;
                        }
                        else
                            f[i][x | 1][y][z ^ 1] = (f[i][x | 1][y][z ^ 1] + (ll)f[i - 1][x][y][z] * pw[i - 1] % mod) % mod;
                    }
                    if (a[i] != 0)
                    {
                        if (x)
                        {
                            f[i][x][y][z] = (f[i][x][y][z] + (ll)f[i - 1][x][y][z] * pw[i - 2] % mod) % mod;
                            f[i][x][y | 1][z ^ 1] = (f[i][x][y | 1][z ^ 1] + (ll)f[i - 1][x][y][z] * pw[i - 2] % mod) % mod;
                        }
                        else
                            f[i][x][y | 1][z ^ 1] = (f[i][x][y | 1][z ^ 1] + (ll)f[i - 1][x][y][z] * pw[i - 1] % mod) % mod;
                    }
                }
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            ans = ((ll)ans + f[n][x][y][1]) % mod;
    printf("%d", ans);
    return 0;
}