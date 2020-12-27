#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
int n, sum, ans = inf;
int head[250], cnt[250];
int dis[250][250], mp[250][250];
ll a[100005];
bool cmp(ll aa, ll bb)
{
    return aa > bb;
}
int main()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(mp, 0x3f, sizeof(mp));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        for (int j = 0; j < 64; ++j)
            if ((a[i] >> j) & 1)
                ++cnt[j];
    }
    for (int i = 0; i < 64; ++i)
        if (cnt[i] > 2)
        {
            printf("3");
            return 0;
        }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        if (a[i] == 0)
        {
            n = i - 1;
            break;
        }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (a[i] & a[j])
            {
                dis[i][j] = 1;
                dis[j][i] = 1;
                mp[i][j] = 1;
                mp[j][i] = 1;
            }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i < k; ++i)
            for (int j = i + 1; j < k; ++j)
                if (dis[i][j] != inf && mp[i][k] != inf && mp[k][j] != inf)
                    ans = min(ans, dis[i][j] + mp[i][k] + mp[k][i]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    if (ans == inf)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}