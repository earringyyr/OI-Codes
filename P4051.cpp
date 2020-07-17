#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[200005];
int n, m = 127, num;
int c[200005], sa[200005], rk[200005], x[200005], y[200005];
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i < n; ++i)
        s[n + i] = s[i];
    n = 2 * n - 1;
    for (int i = 1; i <= n; ++i)
    {
        x[i] = s[i];
        ++c[x[i]];
    }
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
        if (sa[i] <= n / 2 + 1)
            putchar(s[sa[i] + n / 2]);
    return 0;
}