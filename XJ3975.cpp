#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, num;
int st[5005];
int a[5005];
ll ans;
ll fac[15];
void dfs(int k)
{
    if (k == n + 1)
    {
        ans += fac[num];
        return;
    }
    int cnt = 0;
    for (int i = 0; i < (1 << n); i += (1 << k))
    {
        int flg = 1;
        for (int j = 1; j < (1 << k); ++j)
            if (a[i + j - 1] + 1 != a[i + j])
            {
                flg = 0;
                break;
            }
        if (!flg)
            st[++cnt] = i;
    }
    if (cnt > 2)
        return;
    if (!cnt)
        dfs(k + 1);
    else if (cnt == 1)
    {
        int tmp = st[1];
        ++num;
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp + i], a[tmp + (1 << (k - 1)) + i]);
        int flg = 1;
        for (int i = 1; i < (1 << k); ++i)
            if (a[tmp + i - 1] + 1 != a[tmp + i])
            {
                flg = 0;
                break;
            }
        if (flg)
            dfs(k + 1);
        --num;
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp + i], a[tmp + (1 << (k - 1)) + i]);
    }
    else
    {
        int tmp1 = st[1], tmp2 = st[2], flg;
        ++num;
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + i], a[tmp2 + i]);
        flg = 1;
        for (int i = 1; i < (1 << k); ++i)
            if (a[tmp1 + i - 1] + 1 != a[tmp1 + i] || a[tmp2 + i - 1] + 1 != a[tmp2 + i])
            {
                flg = 0;
                break;
            }
        if (flg)
            dfs(k + 1);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + i], a[tmp2 + i]);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + i], a[tmp2 + (1 << (k - 1)) + i]);
        flg = 1;
        for (int i = 1; i < (1 << k); ++i)
            if (a[tmp1 + i - 1] + 1 != a[tmp1 + i] || a[tmp2 + i - 1] + 1 != a[tmp2 + i])
            {
                flg = 0;
                break;
            }
        if (flg)
            dfs(k + 1);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + i], a[tmp2 + (1 << (k - 1)) + i]);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + (1 << (k - 1)) + i], a[tmp2 + i]);
        flg = 1;
        for (int i = 1; i < (1 << k); ++i)
            if (a[tmp1 + i - 1] + 1 != a[tmp1 + i] || a[tmp2 + i - 1] + 1 != a[tmp2 + i])
            {
                flg = 0;
                break;
            }
        if (flg)
            dfs(k + 1);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + (1 << (k - 1)) + i], a[tmp2 + i]);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + (1 << (k - 1)) + i], a[tmp2 + (1 << (k - 1)) + i]);
        flg = 1;
        for (int i = 1; i < (1 << k); ++i)
            if (a[tmp1 + i - 1] + 1 != a[tmp1 + i] || a[tmp2 + i - 1] + 1 != a[tmp2 + i])
            {
                flg = 0;
                break;
            }
        if (flg)
            dfs(k + 1);
        for (int i = 0; i < (1 << (k - 1)); ++i)
            swap(a[tmp1 + (1 << (k - 1)) + i], a[tmp2 + (1 << (k - 1)) + i]);
        --num;
    }
    return;
}
int main()
{
    scanf("%d", &n);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
    for (int i = 0; i < (1 << n); ++i)
        scanf("%d", &a[i]);
    dfs(1);
    printf("%lld", ans);
    return 0;
}