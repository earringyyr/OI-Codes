#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[200005], t[200005];
int ans, lens, lent, pre[200005], suf[200005];
int main()
{
    scanf("%s%s", s, t);
    lens = strlen(s);
    lent = strlen(t);
    for (int i = 0, j = 0; i < lens; ++i)
    {
        if (j < lent && s[i] == t[j])
            ++j;
        pre[i] = j;
    }
    for (int i = lens - 1, j = lent - 1; i >= 0; --i)
    {
        if (j >= 0 && s[i] == t[j])
            --j;
        suf[i] = j;
    }
    suf[lens] = lent - 1;
    for (int i = 0, j = 0, tmp = 0; i <= lens; ++i)
    {
        while (j <= lens && tmp - 1 >= suf[j])
            ++j;
        ans = max(ans, j - i - 1);
        tmp = pre[i];
    }
    printf("%d", ans);
    return 0;
}