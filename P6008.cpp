#include <iostream>
#include <cstdio>
#define mod 1000000007
using namespace std;
int n, m, cnt, ans = 1, num[1005][1005], f[1000005], fa[1000005];
int go[2][2] = {{0, 1}, {-1, 0}};
char s[1005][1005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; ++j)
            num[i][j] = ++cnt;
    }
    for (int i = 1; i <= cnt; ++i)
    {
        fa[i] = i;
        f[i] = 1;
    }
    for (int i = n - 1; i >= 2; --i)
    {
        for (int j = 2; j <= m - 1; ++j)
            if (s[i][j] == '.')
                for (int k = 0; k < 2; ++k)
                {
                    int xx = i + go[0][k];
                    int yy = j + go[1][k];
                    if (s[xx][yy] == '.')
                    {
                        xx = getfather(num[xx][yy]);
                        yy = getfather(num[i][j]);
                        if (xx != yy)
                        {
                            fa[xx] = yy;
                            f[yy] = (long long)f[xx] * f[yy] % mod;
                        }
                    }
                }
        for (int j = 2; j <= m - 1; ++j)
            if (s[i][j] == '.')
            {
                int id = num[i][j];
                if (fa[id] == id)
                    f[id] = (f[id] + 1) % mod;
            }
    }
    for (int i = 2; i <= n - 1; ++i)
        for (int j = 2; j <= m - 1; ++j)
            if (s[i][j] == '.')
                if (fa[num[i][j]] == num[i][j])
                    ans = (long long)ans * f[num[i][j]] % mod;
    printf("%d", ans);
    return 0;
}