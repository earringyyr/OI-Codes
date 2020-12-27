#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt;
int top[55];
int c[55][405], d[55][405];
int ans[820005][5];
void solve(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        int num = 0;
        top[i] = m;
        top[j] = m;
        top[n + 1] = 0;
        for (int k = 1; k <= m; ++k)
        {
            if (d[i][k] <= mid)
                ++num;
            if (d[j][k] <= mid)
                ++num;
        }
        if (num >= m)
        {
            num = 0;
            int sum = 0;
            for (int k = 1; k <= m; ++k)
            {
                if (d[i][k] <= mid && num < m)
                {
                    c[i][k] = 1;
                    ++num;
                    ++sum;
                }
                else
                    c[i][k] = 0;
                if (d[j][k] <= mid && num < m)
                {
                    c[j][k] = 1;
                    ++num;
                }
                else
                    c[j][k] = 0;
            }
            for (int k = 1; k <= sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = j;
                ans[cnt][1] = n + 1;
                ++top[n + 1];
                d[n + 1][top[n + 1]] = d[j][top[j]];
                c[n + 1][top[n + 1]] = c[j][top[j]];
                --top[j];
            }
            for (int k = 1; k <= m; ++k)
                if (c[i][top[i]] == 1)
                {
                    ++cnt;
                    ans[cnt][0] = i;
                    ans[cnt][1] = j;
                    ++top[j];
                    d[j][top[j]] = d[i][top[i]];
                    c[j][top[j]] = c[i][top[i]];
                    --top[i];
                }
                else
                {
                    ++cnt;
                    ans[cnt][0] = i;
                    ans[cnt][1] = n + 1;
                    ++top[n + 1];
                    d[n + 1][top[n + 1]] = d[i][top[i]];
                    c[n + 1][top[n + 1]] = c[i][top[i]];
                    --top[i];
                }
            for (int k = 1; k <= sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = j;
                ans[cnt][1] = i;
                ++top[i];
                d[i][top[i]] = d[j][top[j]];
                c[i][top[i]] = c[j][top[j]];
                --top[j];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = n + 1;
                ans[cnt][1] = i;
                ++top[i];
                d[i][top[i]] = d[n + 1][top[n + 1]];
                c[i][top[i]] = c[n + 1][top[n + 1]];
                --top[n + 1];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = j;
                ans[cnt][1] = n + 1;
                ++top[n + 1];
                d[n + 1][top[n + 1]] = d[j][top[j]];
                c[n + 1][top[n + 1]] = c[j][top[j]];
                --top[j];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = i;
                ans[cnt][1] = j;
                ++top[j];
                d[j][top[j]] = d[i][top[i]];
                c[j][top[j]] = c[i][top[i]];
                --top[i];
            }
            for (int k = 1; k <= m; ++k)
                if (c[n + 1][top[n + 1]] == 1)
                {
                    ++cnt;
                    ans[cnt][0] = n + 1;
                    ans[cnt][1] = i;
                    ++top[i];
                    d[i][top[i]] = d[n + 1][top[n + 1]];
                    c[i][top[i]] = c[n + 1][top[n + 1]];
                    --top[n + 1];
                }
                else
                {
                    ++cnt;
                    ans[cnt][0] = n + 1;
                    ans[cnt][1] = j;
                    ++top[j];
                    d[j][top[j]] = d[n + 1][top[n + 1]];
                    c[j][top[j]] = c[n + 1][top[n + 1]];
                    --top[n + 1];
                }
            ++i;
        }
        else
        {
            num = 0;
            int sum = 0;
            for (int k = 1; k <= m; ++k)
            {
                if (d[j][k] > mid && num < m)
                {
                    c[j][k] = 1;
                    ++num;
                    ++sum;
                }
                else
                    c[j][k] = 0;
                if (d[i][k] > mid && num < m)
                {
                    c[i][k] = 1;
                    ++num;
                }
                else
                    c[i][k] = 0;
            }
            for (int k = 1; k <= sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = i;
                ans[cnt][1] = n + 1;
                ++top[n + 1];
                d[n + 1][top[n + 1]] = d[i][top[i]];
                c[n + 1][top[n + 1]] = c[i][top[i]];
                --top[i];
            }
            for (int k = 1; k <= m; ++k)
                if (c[j][top[j]] == 1)
                {
                    ++cnt;
                    ans[cnt][0] = j;
                    ans[cnt][1] = i;
                    ++top[i];
                    d[i][top[i]] = d[j][top[j]];
                    c[i][top[i]] = c[j][top[j]];
                    --top[j];
                }
                else
                {
                    ++cnt;
                    ans[cnt][0] = j;
                    ans[cnt][1] = n + 1;
                    ++top[n + 1];
                    d[n + 1][top[n + 1]] = d[j][top[j]];
                    c[n + 1][top[n + 1]] = c[j][top[j]];
                    --top[j];
                }
            for (int k = 1; k <= sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = i;
                ans[cnt][1] = j;
                ++top[j];
                d[j][top[j]] = d[i][top[i]];
                c[j][top[j]] = c[i][top[i]];
                --top[i];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = n + 1;
                ans[cnt][1] = j;
                ++top[j];
                d[j][top[j]] = d[n + 1][top[n + 1]];
                c[j][top[j]] = c[n + 1][top[n + 1]];
                --top[n + 1];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = i;
                ans[cnt][1] = n + 1;
                ++top[n + 1];
                d[n + 1][top[n + 1]] = d[i][top[i]];
                c[n + 1][top[n + 1]] = c[i][top[i]];
                --top[i];
            }
            for (int k = 1; k <= m - sum; ++k)
            {
                ++cnt;
                ans[cnt][0] = j;
                ans[cnt][1] = i;
                ++top[i];
                d[i][top[i]] = d[j][top[j]];
                c[i][top[i]] = c[j][top[j]];
                --top[j];
            }
            for (int k = 1; k <= m; ++k)
                if (c[n + 1][top[n + 1]] == 1)
                {
                    ++cnt;
                    ans[cnt][0] = n + 1;
                    ans[cnt][1] = j;
                    ++top[j];
                    d[j][top[j]] = d[n + 1][top[n + 1]];
                    c[j][top[j]] = c[n + 1][top[n + 1]];
                    --top[n + 1];
                }
                else
                {
                    ++cnt;
                    ans[cnt][0] = n + 1;
                    ans[cnt][1] = i;
                    ++top[i];
                    d[i][top[i]] = d[n + 1][top[n + 1]];
                    c[i][top[i]] = c[n + 1][top[n + 1]];
                    --top[n + 1];
                }
            ++j;
        }
    }
    solve(l, mid);
    solve(mid + 1, r);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &d[i][j]);
    solve(1, n);
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++i)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}