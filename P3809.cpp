#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m = 122, num;
int x[1000005], y[1000005];
int sa[1000005], c[1000005];
char s[1000005];
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
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
        printf("%d ", sa[i]);
    return 0;
}