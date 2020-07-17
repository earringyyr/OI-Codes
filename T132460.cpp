#include <iostream>
#include <cstdio>
using namespace std;
int n, type, a, ans, num, vis[256], f[256][256], g[256][256];
char opt[5];
int calc(int x, int y)
{
    if (opt[0] == 'a')
        return x & y;
    if (opt[0] == 'o')
        return x | y;
    return x ^ y;
}
int main()
{
    scanf("%d%s%d", &n, opt, &type);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a);
        if (i >= 2)
        {
            ans = 0;
            num = 0;
            int x = a >> 8, y = a & 255;
            for (int j = 0; j < 256; ++j)
                if (vis[j])
                {
                    int k = (calc(j, x) << 8) | f[j][y];
                    if (k == ans)
                        num += g[j][y];
                    if (k > ans)
                    {
                        ans = k;
                        num = g[j][y];
                    }
                }
            if (type)
                printf("%d %d\n", ans, num);
            else
                printf("%d\n", ans);
        }
        int x = a >> 8, y = a & 255;
        vis[x] = 1;
        for (int j = 0; j < 256; ++j)
        {
            int k = calc(j, y);
            if (k == f[x][j])
                ++g[x][j];
            if (k > f[x][j])
            {
                f[x][j] = k;
                g[x][j] = 1;
            }
        }
    }
    return 0;
}