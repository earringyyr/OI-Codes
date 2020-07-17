#include <iostream>
#include <cstdio>
#define int long long
#define mod 1000000000
using namespace std;
int n, ans, a[500005], s[500005][6];
void solve(int l, int r)
{
    if (l == r)
    {
        ans = (ans + a[l] * a[l] % mod) % mod;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    s[mid][0] = 0;
    s[mid][1] = 0;
    s[mid][2] = 0;
    s[mid][3] = 0;
    s[mid][4] = 0;
    s[mid][5] = 0;
    int mi = a[mid + 1], ma = a[mid + 1];
    for (int i = mid + 1; i <= r; ++i)
    {
        mi = min(mi, a[i]);
        ma = max(ma, a[i]);
        s[i][0] = (s[i - 1][0] + mi) % mod;
        s[i][1] = (s[i - 1][1] + ma) % mod;
        s[i][2] = (s[i - 1][2] + mi * i % mod) % mod;
        s[i][3] = (s[i - 1][3] + ma * i % mod) % mod;
        s[i][4] = (s[i - 1][4] + mi * ma % mod) % mod;
        s[i][5] = (s[i - 1][5] + mi * ma % mod * i % mod) % mod;
    }
    int j = mid + 1, k = mid + 1, minx = a[mid], maxn = a[mid];
    for (int i = mid; i >= l; --i)
    {
        minx = min(minx, a[i]);
        maxn = max(maxn, a[i]);
        while (j <= r && a[j] >= minx)
            ++j;
        while (k <= r && a[k] <= maxn)
            ++k;
        int w1 = min(j - 1, k - 1), w2 = max(j - 1, k - 1);
        ans = (ans + minx * maxn % mod * ((mid + 1 - i + 1 + w1 - i + 1) * (w1 - mid) / 2 % mod) % mod) % mod;
        if (j < k)
            ans = (ans + maxn * (((s[w2][0] - s[w1][0]) % mod * (1 - i) % mod + (s[w2][2] - s[w1][2]) % mod) % mod) % mod) % mod;
        else
            ans = (ans + minx * (((s[w2][1] - s[w1][1]) % mod * (1 - i) % mod + (s[w2][3] - s[w1][3]) % mod) % mod) % mod) % mod;
        ans = (ans + ((s[r][4] - s[w2][4]) % mod * (1 - i) % mod + (s[r][5] - s[w2][5]) % mod) % mod) % mod;
    }
    return;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    solve(1, n);
    printf("%lld", (ans + mod) % mod);
    return 0;
}