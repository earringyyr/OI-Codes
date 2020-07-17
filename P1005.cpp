#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, a[100][100];
__int128 ans, f[100][100];
void write(__int128 x)
{
    if (x > 10)
        write(x / 10);
    putchar(x % 10 | 48);
    return;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    for (int i = 1; i <= n; ++i)
    {
        __int128 fang = 1;
        memset(f, 0, sizeof(f));
        for (int len = m - 1; len >= 0; --len)
        {
            fang *= 2;
            for (int j = 1; j + len - 1 <= m; ++j)
                f[j][len] = max(f[j - 1][len + 1] + fang * a[i][j - 1], f[j][len + 1] + fang * a[i][j + len]);
        }
        __int128 ma = 0;
        for (int i = 1; i <= m; ++i)
            ma = max(ma, f[i][0]);
        ans += ma;
    }
    write(ans);
    return 0;
}