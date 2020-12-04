#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k;
int a[25];
int cnt[6000005], siz[6000005], num[6000005];
bool check(int mid)
{
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= mid; ++i)
        ++cnt[num[i]];
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            if (j & (1 << (i - 1)))
                cnt[j] += cnt[j ^ (1 << i - 1)];
    for (int i = 0; i < (1 << n); ++i)
        if (k * siz[i] > mid - cnt[(1 << n) - i - 1])
            return false;
    return true;
}
int main()
{
    scanf("%d%d", &n, &k);
    m = n * k * 2;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        for (int j = 1; j <= m; j += a[i] * 2)
            for (int k = 0; k < a[i] && j + k <= m; ++k)
                num[j + k] |= (1 << (i - 1));
    }
    for (int i = 1; i < (1 << n); ++i)
        siz[i] = siz[i >> 1] + (i & 1);
    int lef = n * k, rig = m;
    while (lef < rig)
    {
        int mid = (lef + rig) >> 1;
        if (check(mid))
            rig = mid;
        else
            lef = mid + 1;
    }
    printf("%d", lef);
    return 0;
}