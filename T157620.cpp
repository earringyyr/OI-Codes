#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, ans;
int a[1000005], b[1000005], cnt[1000005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
void solve(int l, int r)
{
    if (l > r)
        return;
    int len = r - l + 1, i = l, j = r;
    while (i <= j)
    {
        if (cnt[a[i]] < b[len])
        {
            for (int k = l; k <= i; ++k)
                --cnt[a[k]];
            solve(i + 1, r);
            for (int k = l; k < i; ++k)
                ++cnt[a[k]];
            solve(l, i - 1);
            return;
        }
        if (cnt[a[j]] < b[len])
        {
            for (int k = j; k <= r; ++k)
                --cnt[a[k]];
            solve(l, j - 1);
            for (int k = j + 1; k <= r; ++k)
                ++cnt[a[k]];
            solve(j + 1, r);
            return;
        }
        ++i;
        --j;
    }
    for (int i = l; i <= r; ++i)
        --cnt[a[i]];
    ans = max(ans, len);
    return;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= n; ++i)
        b[i] = read();
    for (int i = 1; i <= n; ++i)
        ++cnt[a[i]];
    solve(1, n);
    printf("%d", ans);
    return 0;
}