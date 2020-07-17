#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n1, n2, m, num, top;
long long cnt, ans;
int sa[400005], rk[400005];
int c[400005], height[400005];
int x[400005], y[400005];
int l[400005], r[400005], st[400005];
char s1[400005], s2[400005];
long long solve(int n, char s[])
{
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(c, 0, sizeof(c));
    m = 27;
    for (int i = 1; i <= n; ++i)
        x[i] = s[i] - 'a' + 1;
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
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k])
            ++k;
        height[rk[i]] = k;
    }
    cnt = 0;
    top = 0;
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
    for (int i = 2; i <= n; ++i)
        cnt += (long long)(r[i] - i) * (i - l[i]) * height[i];
    return cnt;
}
int main()
{
    scanf("%s%s", s1 + 1, s2 + 1);
    n1 = strlen(s1 + 1);
    n2 = strlen(s2 + 1);
    ans -= solve(n1, s1) + solve(n2, s2);
    s1[n1 + 1] = 'z' + 1;
    for (int i = 1; i <= n2; ++i)
        s1[n1 + i + 1] = s2[i];
    ans += solve(n1 + n2 + 1, s1);
    printf("%lld", ans);
    return 0;
}