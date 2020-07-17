#include <iostream>
#include <cstdio>
#define mod 10000
using namespace std;
int t, ma_n, ma_k, sum, f[1005][1005];
int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    return x;
}
int main()
{
    ma_n = read();
    ma_k = read();
    f[0][0] = 1;
    for (register int i = 1; i <= ma_n; ++i)
    {
        sum = 0;
        for (register int j = 0; j <= ma_k; ++j)
        {
            sum = (sum + f[i - 1][j]) % mod;
            f[i][j] = (f[i][j] + sum) % mod;
            if (j - i + 1 >= 0)
                sum = (sum - f[i - 1][j - i + 1]) % mod;
            if (sum < 0)
                sum += mod;
        }
    }
    printf("%d\n", f[ma_n][ma_k]);
    return 0;
}