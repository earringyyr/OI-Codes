#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int nn, n, cnt, ma, mi, ans, num, a[70], use[70], pan;
inline void dfs(int sum, int k, int last)
{
    if (sum == ans)
    {
        cout << num << endl;
        pan = 1;
        return;
    }
    if (k == 0)
    {
        dfs(sum + 1, num, 0);
        return;
    }
    if (k < mi)
        return;
    for (register int i = last + 1; i <= n; ++i)
    {
        if (use[i] == 0 && k >= a[i])
        {
            use[i] = 1;
            dfs(sum, k - a[i], i);
            use[i] = 0;
            if (pan == 1)
                return;
            while (a[i + 1] == a[i])
                ++i;
            if (k == num || k == a[i])
                return;
        }
    }
    return;
}
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int main()
{
    while (cin >> nn)
    {
        if (nn == 0)
            return 0;
        pan = 0;
        n = 0;
        cnt = 0;
        ma = 0;
        mi = 0x3f3f3f;
        ans = 0;
        num = 0;
        memset(use, 0, sizeof(use));
        for (register int i = 1; i <= nn; ++i)
        {
            int lin;
            cin >> lin;
            if (lin <= 50)
            {
                a[++n] = lin;
                cnt += a[n];
                ma = max(ma, a[n]);
                mi = min(mi, a[n]);
            }
        }
        sort(a + 1, a + n + 1, cmp);
        for (register int j = ma; j <= cnt / 2; ++j)
            if (cnt % j == 0)
            {
                num = j;
                ans = cnt / j;
                dfs(0, num, 0);
                if (pan == 1)
                    break;
            }
        if (pan == 0)
            cout << cnt << endl;
    }
    return 0;
}