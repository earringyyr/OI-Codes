#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t, n, q, col, cnt[26], tot[26], num[2005], sum[2005];
char s[2005];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
int main()
{
    t = read();
    for (register int tt = 1; tt <= t; ++tt)
    {
        n = read();
        q = read();
        scanf("%s", s + 1);
        for (register int ttt = 1; ttt <= q; ++ttt)
        {
            col = 0;
            memset(cnt, 0, sizeof(cnt));
            memset(tot, 0, sizeof(tot));
            memset(num, 0, sizeof(num));
            int l, r, len, ans = 0;
            l = read();
            r = read();
            len = r - l + 1;
            for (register int i = l; i <= r; ++i)
                ++cnt[s[i] - 'a'];
            for (int i = 0; i < 26; ++i)
            {
                ++col;
                ++num[cnt[i]];
            }
            for (register int i = 1; i <= len; ++i)
                ++tot[s[i] - 'a'];
            for (int i = 0; i < 26; ++i)
            {
                if (num[tot[i]] <= 0)
                    ++col;
                else
                    --col;
                --num[tot[i]];
            }
            if (!col)
                ++ans;
            for (register int i = len + 1; i <= n; ++i)
            {
                if (num[tot[s[i - len] - 'a']] >= 0)
                    ++col;
                else
                    --col;
                ++num[tot[s[i - len] - 'a']];
                --tot[s[i - len] - 'a'];
                if (num[tot[s[i - len] - 'a']] <= 0)
                    ++col;
                else
                    --col;
                --num[tot[s[i - len] - 'a']];
                if (num[tot[s[i] - 'a']] >= 0)
                    ++col;
                else
                    --col;
                ++num[tot[s[i] - 'a']];
                ++tot[s[i] - 'a'];
                if (num[tot[s[i] - 'a']] <= 0)
                    ++col;
                else
                    --col;
                --num[tot[s[i] - 'a']];
                if (!col)
                    ++ans;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}