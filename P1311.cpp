#include <iostream>
#include <cstdio>
using namespace std;
int n, k, p, cnt[200005][55], pos, a[200005], b[200005];
long long ans;
int main()
{
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i], &b[i]);
        for (int j = 0; j < k; ++j)
            cnt[i][j] = cnt[i - 1][j];
        if (b[i] <= p)
            pos = i;
        ans += cnt[pos][a[i]];
        ++cnt[i][a[i]];
    }
    printf("%lld", ans);
    return 0;
}