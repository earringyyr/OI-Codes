#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int ans, len, a[100005], f[100005][20];
char s[100005];
int dfs(int pos, int num, int lim)
{
    if (pos == 0)
        return num;
    if (!lim && f[pos][num] != -1)
        return f[pos][num];
    int tmp = 0;
    for (int i = 0; i <= (lim ? a[pos] : 9); ++i)
        tmp = (tmp + dfs(pos - 1, num ^ i, lim ? i == a[pos] : 0)) % mod;
    if (!lim)
        f[pos][num] = tmp;
    return tmp;
}
int main()
{
    memset(f, -1, sizeof(f));
    int tt;
    scanf("%d", &tt);
    for (int T = 1; T <= tt; ++T)
    {
        ans = 0;
        scanf("%s", s + 1);
        len = strlen(s + 1);
        for (int i = 1; i <= len; ++i)
        {
            a[len - i + 1] = s[i] - '0';
            ans ^= a[len - i + 1];
        }
        ans -= dfs(len, 0, 1);
        ans = (ans + mod) % mod;
        scanf("%s", s + 1);
        len = strlen(s + 1);
        for (int i = 1; i <= len; ++i)
            a[len - i + 1] = s[i] - '0';
        ans += dfs(len, 0, 1);
        ans %= mod;
        printf("Case #%d: %d\n", T, ans);
    }
    return 0;
}