#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
char s[500005];
int n, m = 26, num, top;
int x[500005], y[500005], c[500005];
int sa[500005], rk[500005], height[500005];
int st[500005], l[500005], r[500005];
ll ans;
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i)
    {
        x[i] = s[i] - 'a' + 1;
        ++c[x[i]];
    }
    for (int i = 2; i <= m; ++i)
        c[i] += c[i - 1];
    for (int i = n; i >= 1; --i)
        sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
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
    }
    st[++top] = 1;
    for (int i = 2; i <= n; ++i)
    {
        while (top && height[st[top]] > height[i])
            r[st[top--]] = i;
        l[i] = st[top];
        st[++top] = i;
    }
    while (top)
        r[st[top--]] = n + 1;
    ans = (ll)n * (n - 1) * (n + 1) / 2;
    for (int i = 2; i <= n; ++i)
        ans -= (ll)2 * (r[i] - i) * (i - l[i]) * height[i];
    printf("%lld", ans);
    return 0;
}