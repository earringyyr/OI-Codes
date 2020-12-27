#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
int n;
int cnt[100005], dep[100005];
ll s;
bool check(int mid)
{
    int d = 0;
    ll num = s, base = 1;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n;)
    {
        ++d;
        for (int j = 1; j <= base && i <= n; ++i, ++j)
        {
            dep[i] = d;
            ++cnt[dep[i]];
            num -= dep[i];
        }
        base *= mid;
    }
    if (num < 0)
        return false;
    int i = n;
    while (num)
    {
        ++d;
        if (cnt[dep[i]] == 1)
            --i;
        --cnt[dep[i]];
        int tmp = min(num, (ll)d - dep[i]);
        num -= tmp;
        dep[i] += tmp;
        ++cnt[dep[i]];
        --i;
    }
    return true;
}
int main()
{
    scanf("%d%lld", &n, &s);
    if (s < 2 * n - 1 || s > (ll)n * (n + 1) / 2)
    {
        printf("No");
        return 0;
    }
    int lef = 1, rig = n - 1;
    while (lef < rig)
    {
        int mid = (lef + rig) >> 1;
        if (check(mid))
            rig = mid;
        else
            lef = mid + 1;
    }
    printf("Yes\n");
    check(lef);
    int num = 1, k = 1;
    for (int i = 2; num < n; ++i)
    {
        int j = num + 1, tmp = num + 1, tot = 0;
        num += cnt[i];
        for (; j <= num; ++j)
        {
            ++tot;
            printf("%d ", k);
            if (tot == lef)
            {
                tot = 0;
                ++k;
            }
        }
        k = tmp;
    }
    return 0;
}