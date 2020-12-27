#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, type, x, y, z, m, hh, tt;
int a[40000005], b[40000005];
int p[100005], l[100005], r[100005];
int st[40000005], pre[40000005];
ll sum[40000005];
__int128 ans;
void write(__int128 x)
{
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}
int main()
{
    scanf("%d%d", &n, &type);
    if (type == 0)
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
    else
    {
        scanf("%d%d%d%d%d%d", &x, &y, &z, &b[1], &b[2], &m);
        for (int i = 1; i <= m; ++i)
            scanf("%d%d%d", &p[i], &l[i], &r[i]);
        for (int i = 1; i <= m; ++i)
            for (int j = p[i - 1] + 1; j <= p[i]; ++j)
            {
                if (j > 2)
                    b[j] = ((ll)x * b[j - 1] + (ll)y * b[j - 2] + z) % (1 << 30);
                a[j] = b[j] % (r[i] - l[i] + 1) + l[i];
            }
    }
    hh = 1;
    tt = 1;
    st[1] = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + a[i];
        while (hh < tt && sum[i] >= 2 * sum[st[hh + 1]] - sum[pre[st[hh + 1]]])
            ++hh;
        pre[i] = st[hh];
        while (hh <= tt && 2 * sum[i] - sum[pre[i]] <= 2 * sum[st[tt]] - sum[pre[st[tt]]])
            --tt;
        st[++tt] = i;
    }
    int d = n;
    while (d)
    {
        ans += (__int128)(sum[d] - sum[pre[d]]) * (sum[d] - sum[pre[d]]);
        d = pre[d];
    }
    write(ans);
    return 0;
}