#include <iostream>
#include <cstdio>
using namespace std;
int n, len, f[5003][5003];
void hp(int k)
{
    int i;
}
int main()
{
    int i;
    scanf("%d", &n);
    f[1][0] = 1;
    f[2][0] = 2;
    for (int i = 3; i <= n; i++)
    {
        for (int j = 0; j <= len; ++j)
            f[i][j] = f[i - 1][j] + f[i - 2][j];
        for (int j = 0; j <= len; ++j)
            if (f[i][j] >= 10)
            {
                f[i][j + 1] += f[i][j] / 10;
                f[i][j] %= 10;
                if (f[i][len + 1])
                    ++len;
            }
    }
    for (i = len; i >= 0; --i)
        printf("%d", f[n][i]);
    return 0;
}