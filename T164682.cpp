#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, k, ans;
int pw[2005];
short num[1100005], len[1100005];
bool zero[1100005][105], ichi[1100005][105];
short mdy[1100005][105];
char s[25][105];
int lowbit(int x)
{
    return x & -x;
}
int Mod(int x)
{
    return x > mod ? x - mod : x;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s[i] + 1);
        len[1 << (i - 1)] = strlen(s[i] + 1);
        for (int j = 1; j <= len[1 << (i - 1)]; ++j)
            if (s[i][j] == '?')
                ++k;
    }
    pw[0] = 1;
    for (int i = 1; i <= k; ++i)
        pw[i] = Mod(pw[i - 1] * 2);
    for (int S = 1; S < (1 << n); ++S)
    {
        if (S != lowbit(S))
            len[S] = min(len[lowbit(S)], len[S - lowbit(S)]);
        num[S] = num[S - lowbit(S)] + 1;
        int tot = 0, tmp = lowbit(S);
        while (tmp)
        {
            ++tot;
            tmp >>= 1;
        }
        for (int i = 1; i <= len[S]; ++i)
        {
            zero[S][i] = zero[S - lowbit(S)][i];
            ichi[S][i] = ichi[S - lowbit(S)][i];
            mdy[S][i] = mdy[S - lowbit(S)][i];
            if (s[tot][i] == '0')
                zero[S][i] = 1;
            if (s[tot][i] == '1')
                ichi[S][i] = 1;
            else if (s[tot][i] == '?')
                ++mdy[S][i];
        }
        int cnt = 0, sum = 0;
        for (int i = 1; i <= len[S]; ++i)
        {
            if (zero[S][i] && ichi[S][i])
                break;
            sum += mdy[S][i] - 1;
            if (zero[S][i] || ichi[S][i])
                ++sum;
            cnt = Mod(cnt + pw[k - sum]);
        }
        if (num[S] & 1)
            ans = Mod(ans + cnt);
        else
            ans = Mod(ans - cnt + mod);
    }
    ans = Mod(ans + pw[k]);
    printf("%d", ans);
    return 0;
}