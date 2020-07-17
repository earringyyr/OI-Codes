#include <iostream>
#include <cstdio>
using namespace std;
int n, maxn = -1, pos, ans, len[1000005];
char s[1000005], ss[500005];
int main()
{
    scanf("%d%s", &n, ss);
    for (int i = 0; i < n; ++i)
    {
        s[2 * i] = '#';
        s[2 * i + 1] = ss[i];
    }
    s[2 * n] = '#';
    n = 2 * n + 1;
    for (int i = 0; i < n; ++i)
    {
        if (i > maxn)
            len[i] = 1;
        else
            len[i] = min(len[2 * pos - i], maxn - i + 1);
        while (i + len[i] < n && i - len[i] >= 0 && s[i + len[i]] == s[i - len[i]])
            ++len[i];
        if (i + len[i] - 1 > maxn)
        {
            if (i % 2 == 0)
                for (int j = maxn - i + 1; j <= len[i]; ++j)
                    if ((j - 1) % 4 == 0 && len[i - (j - 1) / 2] >= (j + 1) / 2)
                        ans = max(ans, j - 1);
            pos = i;
            maxn = i + len[i] - 1;
        }
    }
    printf("%d", ans);
    return 0;
}