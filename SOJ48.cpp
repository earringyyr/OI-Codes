#include <iostream>
#include <cstdio>
#include <algorithm>
#pragma GCC optimize(fast)
using namespace std;
int n, k, ma, ans = 0x7f7f7f7f, t[20], cnt[10];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
inline void dfs(int x)
{
    if (ma >= ans)
        return;
    if (x == n + 1)
    {
        ans = min(ans, ma);
        return;
    }
    for (register int i = 1; i <= k; ++i)
    {
        int maxn = ma;
        cnt[i] += t[x];
        if (cnt[i] > ma)
            ma = cnt[i];
        dfs(x + 1);
        cnt[i] -= t[x];
        ma = maxn;
    }
    return;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (register int i = 1; i <= n; ++i)
        scanf("%d", &t[i]);
    sort(t + 1, t + n + 1, cmp);
    dfs(1);
    printf("%d", ans);
    return 0;
}