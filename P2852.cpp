#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, K, num, ans, a[20005];
int sa[20005], rk[20005], lg[20005];
int height[20005], st[20005][20];
int c[20005], x[20005], y[20005];
int query(int l, int r)
{
    int t = lg[r - l + 1];
    return min(st[l][t], st[r - (1 << t) + 1][t]);
}
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        x[i] = a[i];
        y[i] = x[i];
    }
    sort(y + 1, y + n + 1);
    m = unique(y + 1, y + n + 1) - y - 1;
    for (int i = 1; i <= n; ++i)
        x[i] = lower_bound(y + 1, y + m + 1, x[i]) - y;
    memset(y, 0, sizeof(y));
    for (int i = 1; i <= n; ++i)
        ++c[x[i]];
    for (int i = 2; i <= m; ++i)
        c[i] += c[i - 1];
    for (int i = 1; i <= n; ++i)
        sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        num = 0;
        for (int i = n - k + 1; i <= n; ++i)
            y[++num] = i;
        for (int i = 1; i <= n; ++i)
            if (sa[i] > k)
                y[++num] = sa[i] - k;
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; ++i)
            ++c[x[i]];
        for (int i = 2; i <= m; ++i)
            c[i] += c[i - 1];
        for (int i = n; i >= 1; --i)
        {
            sa[c[x[y[i]]]--] = y[i];
            y[i] = 0;
        }
        swap(x, y);
        x[sa[1]] = 1;
        num = 1;
        for (int i = 2; i <= n; ++i)
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = num;
            else
                x[sa[i]] = ++num;
        if (num == n)
            break;
        m = num;
    }
    for (int i = 1; i <= n; ++i)
        rk[sa[i]] = i;
    int k = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (rk[i] == 1)
            continue;
        if (k)
            --k;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && a[i + k] == a[j + k])
            ++k;
        height[rk[i]] = k;
        st[rk[i]][0] = k;
    }
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= lg[n - i + 1]; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    for (int i = 1; i <= n - K + 2; ++i)
        ans = max(ans, query(i, i + K - 2));
    printf("%d", ans);
    return 0;
}