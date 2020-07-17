#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000007
using namespace std;
int n, m, top[2], num[3005][2], h[3005][2], s[3005][2], a[3005][3005][32];
long long ans[2];
int main()
{
    scanf("%d", &n);
    m = n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &a[i][j][0]);
            for (int k = 1; k <= 31; ++k)
            {
                a[i][j][k] = a[i][j][0] & 1;
                a[i][j][0] >>= 1;
            }
        }
    for (int k = 1; k <= 31; ++k)
    {
        memset(h, 0, sizeof(h));
        memset(s, 0, sizeof(s));
        for (int i = 1; i <= n; ++i)
        {
            top[0] = 0;
            top[1] = 0;
            for (int j = 1; j <= m; ++j)
            {
                if (!a[i][j][k])
                    h[j][0] = i;
                if (a[i][j][k])
                    h[j][1] = i;
                while (top[0] && h[s[top[0]][0]][0] < h[j][0])
                    --top[0];
                while (top[1] && h[s[top[1]][1]][1] < h[j][1])
                    --top[1];
                s[++top[0]][0] = j;
                s[++top[1]][1] = j;
                num[top[0]][0] = num[top[0] - 1][0] + (i - h[s[top[0]][0]][0]) * (s[top[0]][0] - s[top[0] - 1][0]);
                num[top[1]][1] = num[top[1] - 1][1] + (i - h[s[top[1]][1]][1]) * (s[top[1]][1] - s[top[1] - 1][1]);
                ans[0] += (long long)num[top[0]][0] << (k - 1);
                ans[1] += (long long)(i * j - num[top[1]][1]) << (k - 1);
                ans[0] %= mod;
                ans[1] %= mod;
            }
        }
    }
    if (ans[1] < 0)
        ans[1] = (ans[1] + mod) % mod;
    printf("%lld %lld", ans[0], ans[1]);
    return 0;
}