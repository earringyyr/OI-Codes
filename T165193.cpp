#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const ll inf = 0x7f7f7f7f7f7f7f7f;
int n, base, cnt;
int l[505], r[505], tag[505];
ll f[505], g[505][2];
int pos[150005], y[150005];
ll num[150005];
ll mx, ans;
struct node
{
    int x;
    int y;
} a[150005];
bool cmp(node aa, node bb)
{
    return aa.x < bb.x;
}
void rebuild(int k)
{
    ll maxn = -1, id;
    for (int i = l[k]; i <= r[k]; ++i)
    {
        num[i] += (ll)tag[k] * y[i];
        if (num[i] >= maxn)
        {
            id = i;
            maxn = num[i];
        }
    }
    g[k][0] = maxn;
    g[k][1] = y[id];
    tag[k] = 0;
    f[k] = inf;
    for (int i = id + 1; i <= r[k]; ++i)
        f[k] = min(f[k], (maxn - num[i] + y[i] - y[id] - 1) / (y[i] - y[id]));
    return;
}
int main()
{
    memset(f, 0x7f, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        y[i] = a[i].y;
    }
    sort(y + 1, y + n + 1);
    int len = unique(y + 1, y + n + 1) - y - 1;
    for (int i = 1; i <= n; ++i)
        a[i].y = lower_bound(y + 1, y + len + 1, a[i].y) - y;
    base = sqrt(len);
    cnt = (len - 1) / base + 1;
    for (int i = 1; i <= len; ++i)
    {
        pos[i] = (i - 1) / base + 1;
        if (base == 1 || i % base == 1)
            l[pos[i]] = i;
        r[pos[i]] = i;
    }
    for (int i = 1; i <= cnt; ++i)
    {
        g[i][0] = 0;
        g[i][1] = y[r[i]];
    }
    sort(a + 1, a + n + 1, cmp);
    for (int i = 0; i <= n; ++i)
    {
        if (i)
        {
            for (int j = 1; j < pos[a[i].y]; ++j)
            {
                ++tag[j];
                if (tag[j] >= f[j])
                    rebuild(j);
                mx = max(mx, g[j][0] + tag[j] * g[j][1]);
            }
            for (int j = l[pos[a[i].y]]; j <= a[i].y; ++j)
            {
                num[j] += y[j];
                mx = max(mx, num[j] + (ll)tag[pos[a[i].y]] * y[j]);
            }
            rebuild(pos[a[i].y]);
        }
        ans = max(ans, (ll)a[i + 1].x * (n - i) + mx);
    }
    printf("%lld", ans);
    return 0;
}