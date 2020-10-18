#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, L, T, num = 1, ans[100005];
int main()
{
    scanf("%d%d%d", &n, &L, &T);
    for (int i = 1; i <= n; ++i)
    {
        int x, w;
        scanf("%d%d", &x, &w);
        if (w == 1)
            w = 1;
        else
            w = -1;
        ans[i] = x + T * w;
        if (ans[i] >= L)
        {
            num += (ans[i] - L) / L + 1;
            num %= n;
            ans[i] %= L;
        }
        if (ans[i] < 0)
        {
            num -= (-ans[i] - 1) / L + 1;
            num %= n;
            ans[i] = (ans[i] % L + L) % L;
        }
    }
    sort(ans + 1, ans + n + 1);
    num = (num % n + n) % n;
    if (num == 0)
        num = n;
    for (int i = num; i <= n; ++i)
        printf("%d\n", ans[i]);
    for (int i = 1; i < num; ++i)
        printf("%d\n", ans[i]);
    return 0;
}