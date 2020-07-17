#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k, sum, lef = 1, ans = -1, cnt[65];
struct node
{
    int id;
    int pos;
} a[1000005];
bool cmp(node aa, node bb)
{
    return aa.pos < bb.pos;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i)
    {
        int t;
        scanf("%d", &t);
        for (int j = 1; j <= t; ++j)
        {
            ++sum;
            a[sum].id = i;
            scanf("%d", &a[sum].pos);
        }
    }
    sort(a + 1, a + n + 1, cmp);
    sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (!cnt[a[i].id])
            ++sum;
        ++cnt[a[i].id];
        while (cnt[a[lef].id] > 1)
        {
            --cnt[a[lef].id];
            ++lef;
        }
        if (sum == k && (ans == -1 || ans > a[i].pos - a[lef].pos))
            ans = a[i].pos - a[lef].pos;
    }
    printf("%d", ans);
    return 0;
}