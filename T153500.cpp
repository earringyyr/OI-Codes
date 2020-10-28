#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, ans, cnt1, cnt2, num;
int a[100005], b[100005];
int c[100005], d[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++i)
        c[i] = (b[i] - a[i] + 4) % 4;
    for (int i = 1; i <= n; ++i)
    {
        d[i] = c[i] - c[i - 1];
        ans += max(d[i], 0);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (d[i] == -3)
            ++cnt1;
        if (d[i] == -2)
            ++cnt2;
        if (d[i] == 2)
            if (cnt1)
            {
                --cnt1;
                ans -= 1;
                ++num;
            }
        if (d[i] == 3)
        {
            if (cnt1)
            {
                --cnt1;
                ans -= 2;
            }
            else if (cnt2)
            {
                --cnt2;
                ans -= 1;
            }
            else if (num)
                ans -= 1;
        }
    }
    printf("%d", ans);
    return 0;
}