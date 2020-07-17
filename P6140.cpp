#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, num, top;
int sa[1000005], rk[1000005];
int c[1000005];
int x[1000005], y[1000005];
char s[1000005], ans[500005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf(" %c", &s[i]);
    for (int i = 1; i <= n; ++i)
    {
        s[2 * n - i + 1] = s[i];
        x[i] = s[i] - 'A' + 1;
        x[2 * n - i + 1] = s[i] - 'A' + 1;
    }
    n = 2 * n;
    m = 26;
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
    n /= 2;
    int l = 1, r = n;
    while (l < r)
    {
        if (s[l] < s[r])
            ans[++top] = s[l++];
        else if (s[l] > s[r])
            ans[++top] = s[r--];
        else if (s[l] == s[r])
        {
            int i = l, j = 2 * n - r + 1;
            if (rk[i] < rk[j])
                ans[++top] = s[l++];
            else
                ans[++top] = s[r--];
        }
    }
    ans[++top] = s[l];
    for (int i = 1; i <= n; ++i)
    {
        putchar(ans[i]);
        if (i % 80 == 0)
            putchar('\n');
    }
    return 0;
}