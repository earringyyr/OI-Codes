#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mod 1000000007
using namespace std;
int n, s, e, ans, dp[2005][2005];
char S[2005];
int main()
{
    char ch = getchar();
    while (ch < 'A' || ch > 'Z')
        ch = getchar();
    while (ch >= 'A' && ch <= 'Z')
    {
        S[++n] = ch;
        ch = getchar();
    }
    scanf("%d%d", &s, &e);
    dp[0][0] = 1;
    for (int i = 0; i <= n - 2; ++i)
        for (int j = (i > 0); j <= i; ++j)
        {
            if (dp[i][j] == 0)
                continue;
            char k = S[i + 1];
            long long val = dp[i][j];
            int free = j;
            if (i >= s)
                free--;
            if (i >= e)
                free--;
            if (free < 0)
                continue;
            if (i + 1 == s)
            {
                if (k == 'R' || k == 'B')
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] + val) % mod;
                if (k == 'L' || k == 'B')
                    dp[i + 1][j] = (dp[i + 1][j] + val * free) % mod;
            }
            else if (i + 1 == e)
            {
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + val) % mod;
                dp[i + 1][j] = (dp[i + 1][j] + val * free) % mod;
            }
            else
            {
                if (k == 'R' || k == 'B')
                    dp[i + 1][j + 1] = (dp[i + 1][j + 1] + val) % mod;
                if (i + 1 > s && (k == 'R' || k == 'B'))
                    dp[i + 1][j] = (dp[i + 1][j] + val) % mod;
                if (i + 1 > s && (k == 'L' || k == 'B') && j)
                    dp[i + 1][j - 1] = (dp[i + 1][j - 1] + val * free) % mod;
                if (i + 1 > e && (k == 'L' || k == 'B'))
                    dp[i + 1][j] = (dp[i + 1][j] + val) % mod;
                if (i + 1 > e && (k == 'L' || k == 'B') && j)
                    dp[i + 1][j - 1] = (dp[i + 1][j - 1] + val * free) % mod;
                if (k == 'L' || k == 'B')
                    dp[i + 1][j] = (dp[i + 1][j] + val * free) % mod;
                if (k == 'R' || k == 'B')
                    dp[i + 1][j] = (dp[i + 1][j] + val * free) % mod;
                if (free >= 2 && (k == 'L' || k == 'B'))
                    dp[i + 1][j - 1] = (dp[i + 1][j - 1] + free * (free - 1) % mod * val) % mod;
            }
        }
    if (n == s)
    {
        if (S[n] == 'L' || S[n] == 'B')
            ans = dp[n - 1][1];
    }
    else if (n == e)
        ans = dp[n - 1][1];
    else if (S[n] == 'L' || S[n] == 'B')
        ans = dp[n - 1][2];
    printf("%d", ans);
    return 0;
}