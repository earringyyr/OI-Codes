#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int l, s, t, m, ans, len, a[105], b[105], vis[100005], f[100005];
int main()
{
    scanf("%d%d%d%d", &l, &s, &t, &m);
    len = 90;
    for (int i = 1; i <= m; ++i)
        scanf("%d", &b[i]);
    if (s == t)
    {
        for (int i = 1; i <= m; ++i)
            if (b[i] % s == 0)
                ++ans;
        printf("%d", ans);
        return 0;
    }
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; ++i)
    {
        int d = b[i] - b[i - 1];
        if (d > len)
            d = len;
        a[i] = a[i - 1] + d;
        vis[a[i]] = 1;
    }
    l = a[m] + len;
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= l; ++i)
        for (int j = s; j <= t; ++j)
            if (i >= j)
                f[i] = min(f[i], f[i - j] + vis[i]);
    ans = 0x7f7f7f7f;
    for (int i = a[m]; i <= l; ++i)
        ans = min(ans, f[i]);
    printf("%d", ans);
    return 0;
}