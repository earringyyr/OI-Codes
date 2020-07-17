#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, pos, maxn, ans, len[2005];
char s[2005], ss[2005];
int main()
{
    scanf("%s", ss);
    n = strlen(ss);
    for (int i = 0; i < n; ++i)
    {
        s[2 * i] = '#';
        s[2 * i + 1] = ss[i];
    }
    s[2 * n] = '#';
    n = 2 * n + 1;
    for (int i = 0; i < n; ++i)
    {
        if (i <= maxn)
            len[i] = min(len[2 * pos - i], maxn - i + 1);
        else
            len[i] = 1;
        while (i + len[i] < n && i - len[i] >= 0 && s[i + len[i]] == s[i - len[i]])
            ++len[i];
        if (i + len[i] - 1 > maxn)
        {
            maxn = i + len[i] - 1;
            pos = i;
        }
    }
    for (int i = 0; i < n; ++i)
        ans += len[i] / 2;
    printf("%d", ans);
    return 0;
}