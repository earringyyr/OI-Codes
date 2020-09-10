#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int K, la, lb, pos, L, R, n, m = 90, num, ans;
int cnt[100005];
int x[100005], y[100005];
int sa[100005], c[100005];
int rk[100005], height[100005];
int lg[100005], st[100005][20];
char a[100005], b[100005], s[100005];
int query(int l, int r)
{
    if (l > r)
        swap(l, r);
    return min(st[l + 1][lg[r - l]], st[r - (1 << lg[r - l]) + 1][lg[r - l]]);
}
void dfs(int x, int y, int w)
{
    if (w < 0)
        return;
    int lcp = query(rk[x], rk[y]);
    x += lcp;
    y += lcp;
    if (x == la + 1 || y == n + 1)
    {
        int d = w - (la - x + 1);
        if (d < 0)
            return;
        int l = max(y - d - 1, pos), r = min(y + d - 1, n);
        L = min(l, L);
        R = max(r + 1, R);
        ++cnt[l];
        --cnt[r + 1];
        return;
    }
    dfs(x + 1, y, w - 1);
    dfs(x, y + 1, w - 1);
    dfs(x + 1, y + 1, w - 1);
    return;
}
int main()
{
    scanf("%d", &K);
    scanf("%s%s", a + 1, b + 1);
    la = strlen(a + 1);
    lb = strlen(b + 1);
    n = la + lb + 1;
    for (int i = 1; i <= la; ++i)
        s[i] = a[i];
    s[la + 1] = '#';
    for (int i = 1; i <= lb; ++i)
        s[la + i + 1] = b[i];
    for (int i = 1; i <= n; ++i)
    {
        x[i] = s[i];
        ++c[x[i]];
    }
    for (int i = 2; i <= m; ++i)
        c[i] += c[i - 1];
    for (int i = n; i >= 1; --i)
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
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k])
            ++k;
        height[rk[i]] = k;
        st[rk[i]][0] = height[rk[i]];
    }
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= lg[n - i + 1]; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    for (int i = 1; i <= lb; ++i)
    {
        L = n + 2;
        R = 0;
        pos = la + i + 1;
        dfs(1, la + i + 1, K);
        for (int j = L; j <= R; ++j)
        {
            cnt[j] += cnt[j - 1];
            if (cnt[j] > 0)
                ++ans;
        }
        for (int j = L; j <= R; ++j)
            cnt[j] = 0;
    }
    printf("%d", ans);
    return 0;
}