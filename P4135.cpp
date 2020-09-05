#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, c, m, len, Ans, a[100005], l[1005], r[1005], pos[100005];
int sum[1005][100005], ans[1005][1005], num[100005];
int main()
{
    scanf("%d%d%d", &n, &c, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
    {
        pos[i] = i / len + 1;
        if (!l[pos[i]])
            l[pos[i]] = i;
        r[pos[i]] = i;
    }
    for (int i = 1; i <= n / len + 1; ++i)
    {
        for (int j = l[i]; j <= r[i]; ++j)
        {
            ++sum[i][a[j]];
            ++num[a[j]];
            if (num[a[j]] % 2 == 0)
                ++ans[i][i];
            else if (num[a[j]] > 1)
                --ans[i][i];
        }
        for (int j = i - 1; j >= 1; --j)
        {
            ans[j][i] = ans[j + 1][i];
            for (int k = l[j]; k <= r[j]; ++k)
            {
                ++num[a[k]];
                if (num[a[k]] % 2 == 0)
                    ++ans[j][i];
                else if (num[a[k]] > 1)
                    --ans[j][i];
            }
        }
        memset(num, 0, sizeof(num));
        for (int j = 1; j <= c; ++j)
            sum[i][j] += sum[i - 1][j];
    }
    for (int T = 1; T <= m; ++T)
    {
        int L, R;
        scanf("%d%d", &L, &R);
        L = (L + Ans) % n + 1;
        R = (R + Ans) % n + 1;
        if (L > R)
            swap(L, R);
        if (pos[L] == pos[R])
        {
            Ans = 0;
            for (int i = L; i <= R; ++i)
            {
                ++num[a[i]];
                if (num[a[i]] % 2 == 0)
                    ++Ans;
                else if (num[a[i]] > 1)
                    --Ans;
            }
            for (int i = L; i <= R; ++i)
                --num[a[i]];
            printf("%d\n", Ans);
            continue;
        }
        Ans = ans[pos[L] + 1][pos[R] - 1];
        for (int i = L; i <= r[pos[L]]; ++i)
        {
            ++num[a[i]];
            if ((num[a[i]] + sum[pos[R] - 1][a[i]] - sum[pos[L]][a[i]]) % 2 == 0)
                ++Ans;
            else if ((num[a[i]] + sum[pos[R] - 1][a[i]] - sum[pos[L]][a[i]]) > 1)
                --Ans;
        }
        for (int i = l[pos[R]]; i <= R; ++i)
        {
            ++num[a[i]];
            if ((num[a[i]] + sum[pos[R] - 1][a[i]] - sum[pos[L]][a[i]]) % 2 == 0)
                ++Ans;
            else if ((num[a[i]] + sum[pos[R] - 1][a[i]] - sum[pos[L]][a[i]]) > 1)
                --Ans;
        }
        for (int i = L; i <= r[pos[L]]; ++i)
            --num[a[i]];
        for (int i = l[pos[R]]; i <= R; ++i)
            --num[a[i]];
        printf("%d\n", Ans);
    }
    return 0;
}