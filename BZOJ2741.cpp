#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, m, len, cnt, ans;
int a[12005], rt[12005], pos[12005];
int l[5005], r[5005];
int num[400005], tr[400005][2];
int f[5005][5005];
void insert(int y, int &x, int t, int val)
{
    x = ++cnt;
    memcpy(tr[x], tr[y], sizeof(tr[y]));
    num[x] = num[y] + 1;
    if (t == -1)
        return;
    int k = (val >> t) & 1;
    insert(tr[y][k], tr[x][k], t - 1, val);
    return;
}
int query(int x, int y, int val)
{
    int tot = 0;
    for (int i = 30; i >= 0; --i)
    {
        int k = ((val >> i) & 1) ^ 1;
        if (num[tr[y][k]] - num[tr[x][k]] > 0)
        {
            tot += (1 << i);
            x = tr[x][k];
            y = tr[y][k];
        }
        else
        {
            x = tr[x][k ^ 1];
            y = tr[y][k ^ 1];
        }
    }
    return tot;
}
int main()
{
    scanf("%d%d", &n, &m);
    len = sqrt(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        a[i] = a[i - 1] ^ a[i];
        insert(rt[i - 1], rt[i], 30, a[i]);
        pos[i] = i / len;
        if (i == 1 || pos[i] != pos[i - 1])
            l[pos[i]] = i;
        r[pos[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = pos[i]; j <= pos[n]; ++j)
            f[pos[i]][j] = max(f[pos[i]][j], query(rt[i - 1], rt[r[j]], a[i - 1]));
    for (int i = 1; i <= m; ++i)
    {
        int L, R;
        scanf("%d%d", &L, &R);
        L = ((long long)L + ans) % n + 1;
        R = ((long long)R + ans) % n + 1;
        if (L > R)
            swap(L, R);
        ans = 0;
        for (int j = pos[L] + 1; j <= pos[R] - 1; ++j)
            for (int k = j; k <= pos[R] - 1; ++k)
                ans = max(ans, f[j][k]);
        for (int j = L; j <= min(R, r[pos[L]]); ++j)
            ans = max(ans, query(rt[j - 1], rt[R], a[j - 1]));
        for (int j = max(L, l[pos[R]]); j <= R; ++j)
            ans = max(ans, query(rt[L - 1], rt[j], a[j]));
        printf("%d\n", ans);
    }
    return 0;
}