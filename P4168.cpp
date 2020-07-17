#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, x, len, k, cnt;
int a[40005], b[40005], pos[40005], num[40005];
int l[205], r[205], f[205][205], w[205][40005];
int query(int lx, int rx)
{
    int ans = -1, ll = lx, rr = rx;
    if (pos[lx] == pos[rx])
    {
        for (int i = lx; i <= rx; ++i)
            num[a[i]] = 0;
        for (int i = lx; i <= rx; ++i)
        {
            ++num[a[i]];
            if (ans == -1 || num[a[i]] > num[ans] || (num[a[i]] == num[ans] && a[i] < ans))
                ans = a[i];
        }
        return ans;
    }
    while (lx != l[pos[lx]])
        ++lx;
    while (rx != r[pos[rx]])
        --rx;
    if (pos[lx] <= pos[rx])
    {
        ans = f[pos[lx]][pos[rx]];
        num[ans] = w[pos[rx]][ans] - w[pos[lx] - 1][ans];
    }
    for (int i = ll; i <= lx - 1; ++i)
        num[a[i]] = w[pos[rx]][a[i]] - w[pos[lx] - 1][a[i]];
    for (int i = rx + 1; i <= rr; ++i)
        num[a[i]] = w[pos[rx]][a[i]] - w[pos[lx] - 1][a[i]];
    --lx;
    ++rx;
    for (int i = ll; i <= lx; ++i)
    {
        ++num[a[i]];
        if (ans == -1 || num[a[i]] > num[ans] || (num[a[i]] == num[ans] && a[i] < ans))
            ans = a[i];
    }
    for (int i = rx; i <= rr; ++i)
    {
        ++num[a[i]];
        if (ans == -1 || num[a[i]] > num[ans] || (num[a[i]] == num[ans] && a[i] < ans))
            ans = a[i];
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    k = sqrt(n);
    for (int i = 1; i <= n; i += k)
    {
        ++cnt;
        l[cnt] = i;
        r[cnt] = min(n, i + k - 1);
        for (int j = i; j <= min(n, i + k - 1); ++j)
            pos[j] = cnt;
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    for (int i = 1; i <= cnt; ++i)
    {
        for (int j = 1; j <= n; ++j)
            w[i][a[j]] = w[i - 1][a[j]];
        for (int j = l[i]; j <= r[i]; ++j)
        {
            ++w[i][a[j]];
            if (f[i][i] == -1 || w[i][a[j]] - w[i - 1][a[j]] > w[i][f[i][i]] - w[i - 1][f[i][i]] || (w[i][a[j]] - w[i - 1][a[j]] == w[i][f[i][i]] - w[i - 1][f[i][i]] && a[j] < f[i][i]))
                f[i][i] = a[j];
        }
    }
    for (int i = 1; i <= cnt; ++i)
        for (int j = i + 1; j <= cnt; ++j)
        {
            f[i][j] = f[i][j - 1];
            for (int k = l[j]; k <= r[j]; ++k)
                if (w[j][a[k]] - w[i - 1][a[k]] > w[j][f[i][j]] - w[i - 1][f[i][j]] || (w[j][a[k]] - w[i - 1][a[k]] == w[j][f[i][j]] - w[i - 1][f[i][j]] && a[k] < f[i][j]))
                    f[i][j] = a[k];
        }
    for (int i = 1; i <= m; ++i)
    {
        int lx, rx;
        scanf("%d%d", &lx, &rx);
        lx = (lx + x - 1) % n + 1;
        rx = (rx + x - 1) % n + 1;
        if (lx > rx)
            swap(lx, rx);
        x = b[query(lx, rx)];
        printf("%d\n", x);
    }
    return 0;
}