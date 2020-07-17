#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 10007
using namespace std;
int n, m, len, h, t, sum, ans;
int bo[6005], nxt[6005], l[6005];
int tr[6005][26], f[105][6005];
char s[105];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s);
        len = strlen(s);
        int rt = 0;
        for (int i = 0; i < len; ++i)
        {
            if (!tr[rt][s[i] - 'A'])
                tr[rt][s[i] - 'A'] = ++sum;
            rt = tr[rt][s[i] - 'A'];
        }
        bo[rt] = 1;
    }
    for (int i = 0; i < 26; ++i)
        if (tr[0][i])
            l[++t] = tr[0][i];
    while (h < t)
    {
        ++h;
        int rt = l[h];
        for (int i = 0; i < 26; ++i)
            if (!tr[rt][i])
                tr[rt][i] = tr[nxt[rt]][i];
            else
            {
                nxt[tr[rt][i]] = tr[nxt[rt]][i];
                bo[tr[rt][i]] |= bo[tr[nxt[rt]][i]];
                l[++t] = tr[rt][i];
            }
    }
    f[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j <= sum; ++j)
            for (int k = 0; k < 26; ++k)
                if (!bo[tr[j][k]])
                    f[i][tr[j][k]] = (f[i][tr[j][k]] + f[i - 1][j]) % mod;
    ans = 1;
    for (int i = 1; i <= m; ++i)
        ans = (ans * 26) % mod;
    for (int i = 0; i <= sum; ++i)
        ans = (ans - f[m][i]) % mod;
    ans = (ans + mod) % mod;
    cout << ans;
    return 0;
}