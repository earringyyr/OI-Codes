#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, s, ans[100005];
int num[100005][30], sum[100005][30];
int a[100005], b[25005], nxt[25005];
void kmp()
{
    int x = 0, y = -1;
    nxt[0] = -1;
    while (x < k)
    {
        if (y == -1 || (sum[x + 1][b[x]] - sum[x - y][b[x]] == sum[y + 1][b[y]] && sum[x + 1][b[x] - 1] - sum[x - y][b[x] - 1] == sum[y + 1][b[y] - 1]))
        {
            ++x;
            ++y;
            nxt[x] = y;
        }
        else
            y = nxt[y];
    }
    return;
}
int main()
{
    while (~scanf("%d%d%d", &n, &k, &s))
    {
        ans[0] = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &a[i]);
            memcpy(num[i + 1], num[i], sizeof(num[i]));
            for (int j = a[i]; j <= s; ++j)
                ++num[i + 1][j];
        }
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &b[i]);
            memcpy(sum[i + 1], sum[i], sizeof(sum[i]));
            for (int j = b[i]; j <= s; ++j)
                ++sum[i + 1][j];
        }
        kmp();
        int j = 0;
        for (int i = 0; i < n; ++i)
        {
            if (num[i + 1][a[i]] - num[i - j][a[i]] != sum[j + 1][b[j]] || num[i + 1][a[i] - 1] - num[i - j][a[i] - 1] != sum[j + 1][b[j] - 1])
            {
                j = nxt[j];
                if (j != -1)
                    --i;
                else
                    j = 0;
                continue;
            }
            if (j == k - 1)
            {
                ans[++ans[0]] = i - k + 2;
                j = nxt[k];
                continue;
            }
            ++j;
        }
        for (int i = 0; i <= ans[0]; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}