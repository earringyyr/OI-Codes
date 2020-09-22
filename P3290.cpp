#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
const char ch[3] = {'W', 'B', 'X'};
int n, m, c, q, ans, nxt[2][15], f[2][5005][10][10];
char s[2][15];
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &c, &q);
    while (q--)
    {
        ans = ksm(3, m * n);
        for (int i = 0; i <= 1; ++i)
        {
            scanf("%s", s[i] + 1);
            nxt[i][1] = 0;
            int x = 1, y = 0;
            while (x <= c)
            {
                if (!y || s[i][x] == s[i][y])
                {
                    ++x;
                    ++y;
                    nxt[i][x] = y;
                }
                else
                    y = nxt[i][y];
            }
        }
        memset(f[0], 0, sizeof(f[0]));
        f[0][0][0][0] = 1;
        int base = 1 << (m - c + 1);
        int id = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                id ^= 1;
                memset(f[id], 0, sizeof(f[id]));
                for (int msk = 0; msk < base; ++msk)
                    for (int k = 0; k <= c; ++k)
                        for (int l = 0; l <= c; ++l)
                            if (f[id ^ 1][msk][k][l])
                                for (int dim = 0; dim <= 2; ++dim)
                                {
                                    int nk = k + 1;
                                    while (nk && (nk > c || s[0][nk] != ch[dim]))
                                        nk = nxt[0][nk];
                                    int nl = l + 1;
                                    while (nl && (nl > c || s[1][nl] != ch[dim]))
                                        nl = nxt[1][nl];
                                    if (nl == c && j >= c && (msk & (1 << (j - c))))
                                        continue;
                                    int nmsk = msk;
                                    if (j >= c)
                                    {
                                        nmsk |= (1 << (j - c));
                                        if (nk != c)
                                            nmsk ^= (1 << (j - c));
                                    }
                                    f[id][nmsk][nk][nl] = (f[id][nmsk][nk][nl] + f[id ^ 1][msk][k][l]) % mod;
                                }
            }
            for (int msk = 0; msk < base; ++msk)
                for (int k = 0; k <= c; ++k)
                    for (int l = 0; l <= c; ++l)
                        if (k || l)
                        {
                            f[id][msk][0][0] = (f[id][msk][0][0] + f[id][msk][k][l]) % mod;
                            f[id][msk][k][l] = 0;
                        }
        }
        for (int msk = 0; msk < base; ++msk)
            ans = (ans - f[id][msk][0][0] + mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}