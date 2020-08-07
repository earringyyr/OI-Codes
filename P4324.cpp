#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, pos, maxn, ans, base = 2333, mod = 998244353;
int len[200005], h[100005], hsh[100005][2][2];
char a[100005], b[100005], c[200005];
int gethash(int type, int id, int l, int r)
{
    if (type == 0)
        return (hsh[r][id][0] - (ll)hsh[l - 1][id][0] * h[r - l + 1] % mod + mod) % mod;
    return (hsh[l][id][1] - (ll)hsh[r + 1][id][1] * h[r - l + 1] % mod + mod) % mod;
}
void calc()
{
    for (int i = 1; i <= n; ++i)
    {
        c[2 * i - 1] = '#';
        c[2 * i] = a[i];
    }
    c[2 * n + 1] = '#';
    h[0] = 1;
    for (int i = 1; i <= n; ++i)
        h[i] = (ll)h[i - 1] * base % mod;
    for (int i = 1; i <= n; ++i)
    {
        hsh[i][0][0] = ((ll)hsh[i - 1][0][0] * base % mod + (a[i] - 'A')) % mod;
        hsh[i][1][0] = ((ll)hsh[i - 1][1][0] * base % mod + (b[i] - 'A')) % mod;
    }
    for (int i = n; i >= 1; --i)
    {
        hsh[i][0][1] = ((ll)hsh[i + 1][0][1] * base % mod + (a[i] - 'A')) % mod;
        hsh[i][1][1] = ((ll)hsh[i + 1][1][1] * base % mod + (b[i] - 'A')) % mod;
    }
    pos = 0;
    maxn = -1;
    for (int i = 1; i <= 2 * n + 1; ++i)
    {
        if (i <= maxn)
            len[i] = min(maxn - i + 1, len[2 * pos - i]);
        else
            len[i] = 1;
        while (i - len[i] >= 0 && i + len[i] <= 2 * n + 2 && c[i - len[i]] == c[i + len[i]])
            ++len[i];
        if (i + len[i] - 1 >= maxn)
        {
            pos = i;
            maxn = i + len[i] - 1;
        }
    }
    int l, r;
    for (int i = 1; i <= 2 * n + 1; ++i)
    {
        int posl = (i - len[i]) / 2, posr = (i + len[i]) / 2;
        l = 0;
        r = min(posl + 1, n - posr + 2);
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (posl - mid + 1 >= 1 && posr + mid - 2 <= n && gethash(0, 0, posl - mid + 1, posl) == gethash(1, 1, posr - 1, posr + mid - 2))
                l = mid;
            else if (posl - mid + 2 >= 1 && posr + mid - 1 <= n && gethash(0, 1, posl - mid + 2, posl + 1) == gethash(1, 0, posr, posr + mid - 1))
                l = mid;
            else
                r = mid - 1;
        }
        ans = max(ans, l * 2 + len[i] - 1);
    }
    return;
}
int main()
{
    scanf("%d%s%s", &n, a + 1, b + 1);
    calc();
    for (int i = 1; i <= n; ++i)
        swap(a[i], b[i]);
    calc();
    printf("%d\n", ans);
    return 0;
}