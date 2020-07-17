#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, len[3];
long long hs[3][1000005][3], base = 2333, ksm[1000005][3];
long long mod1 = 1e9 + 7, mod2 = 1e9 + 9, mod3 = 19260817;
char s[1000005];
long long geths(int w, int k, int l, int r)
{
    if (w == 1)
        return ((hs[k][r][1] - hs[k][l - 1][1] * ksm[r - l + 1][1]) % mod1 + mod1) % mod1;
    if (w == 2)
        return ((hs[k][r][2] - hs[k][l - 1][2] * ksm[r - l + 1][2]) % mod2 + mod2) % mod2;
}
int main()
{
    scanf("%d", &n);
    ksm[0][1] = 1;
    ksm[0][2] = 1;
    for (int i = 1; i <= 1000000; ++i)
    {
        ksm[i][1] = ksm[i - 1][1] * base % mod1;
        ksm[i][2] = ksm[i - 1][2] * base % mod2;
    }
    for (int t = 1; t <= n; ++t)
    {
        scanf("%s", s + 1);
        len[2] = strlen(s + 1);
        for (int i = 1; i <= len[2]; ++i)
        {
            hs[2][i][1] = (hs[2][i - 1][1] * base + s[i] - 'a') % mod1;
            hs[2][i][2] = (hs[2][i - 1][2] * base + s[i] - 'a') % mod2;
        }
        int pos = 0;
        for (int i = 1, j = len[1]; i <= len[2] && j >= 1; ++i, --j)
            if (geths(1, 1, j, len[1]) == geths(1, 2, 1, i))
                if (geths(2, 1, j, len[1]) == geths(2, 2, 1, i))
                    pos = i;
        for (int i = pos + 1; i <= len[2]; ++i)
        {
            ++len[1];
            hs[1][len[1]][1] = (hs[1][len[1] - 1][1] * base + s[i] - 'a') % mod1;
            hs[1][len[1]][2] = (hs[1][len[1] - 1][2] * base + s[i] - 'a') % mod2;
            putchar(s[i]);
        }
    }
    return 0;
}