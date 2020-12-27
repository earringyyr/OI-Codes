#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, m, id = 1;
int h[705][705];
int cnt[4005];
ll ans = 1e18, minx[2];
ll f[705][4005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &h[i][j]);
            h[i][j] += 1000;
        }
    int flg = 1;
    for (int i = 2; i <= m; ++i)
        if (h[1][i] <= h[1][i - 1])
        {
            flg = 0;
            break;
        }
    if (!flg)
        puts("-1");
    else
    {
        for (int i = 2; i <= n; ++i)
        {
            int L = 0, R = 0;
            ll sum = 0;
            memset(cnt, 0, sizeof(cnt));
            for (int j = 0; j <= 4000; ++j)
            {
                f[i][j] = minx[0];
                if (j == 0)
                    for (int k = 1; k <= m; ++k)
                    {
                        int tmp = (j - h[1][m] + h[1][k]) - h[i][k];
                        if (h[1][m] + h[i][k] - h[1][k] >= 0)
                            ++cnt[h[1][m] + h[i][k] - h[1][k]];
                        if (tmp >= 0)
                            ++L;
                        else
                            ++R;
                        sum += abs(tmp);
                    }
                else
                {
                    sum += L;
                    sum -= R;
                    L += cnt[j];
                    R -= cnt[j];
                }
                f[i][j] += sum;
                if (j == 0)
                    minx[1] = f[i][j];
                else
                    minx[1] = min(minx[1], f[i][j]);
            }
            swap(minx[0], minx[1]);
        }
        printf("%lld\n", minx[0]);
    }
    for (int i = 1; i <= n; ++i)
        if (h[i][1] > h[id][1])
            id = i;
    for (int i = 2; i <= m; ++i)
    {
        int L = 0, R = 0;
        ll sum = 0;
        memset(cnt, 0, sizeof(cnt));
        minx[0] = f[i - 1][h[id][1] + i - 2];
        for (int j = h[id][1] + i - 1; j <= 4000; ++j)
        {
            f[i][j] = minx[0];
            if (j == h[id][1] + i - 1)
                for (int k = 1; k <= n; ++k)
                {
                    int tmp = (j + h[k][1] - h[id][1]) - h[k][i];
                    if (h[id][1] + h[k][i] - h[k][1] >= 0)
                        ++cnt[h[id][1] + h[k][i] - h[k][1]];
                    if (tmp >= 0)
                        ++L;
                    else
                        ++R;
                    sum += abs(tmp);
                }
            else
            {
                sum += L;
                sum -= R;
                L += cnt[j];
                R -= cnt[j];
            }
            f[i][j] += sum;
            minx[0] = min(minx[0], f[i - 1][j]);
        }
    }
    for (int j = h[id][1] + m - 1; j <= 4000; ++j)
        ans = min(ans, f[m][j]);
    printf("%lld", ans);
    return 0;
}