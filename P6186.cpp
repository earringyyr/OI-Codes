#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
int n, m, c[200005], d[200005], p[200005], ans[200005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= n)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int query(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
void addd(int x, int val)
{
    while (x <= n)
    {
        d[x] += val;
        x += lowbit(x);
    }
    return;
}
int queryy(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += d[x];
        x -= lowbit(x);
    }
    return ans;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &p[i]);
    for (int i = 1; i <= n; ++i)
    {
        add(p[i], 1);
        ans[i] = i - query(p[i]);
    }
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i)
    {
        add(ans[i] + 1, 1);
        addd(ans[i] + 1, ans[i]);
    }
    for (int i = 1; i <= m; ++i)
    {
        int t, cc;
        scanf("%lld%lld", &t, &cc);
        cc = min(cc, n);
        if (t == 1)
        {
            add(ans[cc] + 1, -1);
            addd(ans[cc] + 1, -ans[cc]);
            add(ans[cc + 1] + 1, -1);
            addd(ans[cc + 1] + 1, -ans[cc + 1]);
            if (p[cc] > p[cc + 1])
                --ans[cc + 1];
            else
                ++ans[cc];
            swap(ans[cc], ans[cc + 1]);
            swap(p[cc], p[cc + 1]);
            add(ans[cc] + 1, 1);
            addd(ans[cc] + 1, ans[cc]);
            add(ans[cc + 1] + 1, 1);
            addd(ans[cc + 1] + 1, ans[cc + 1]);
        }
        else
            printf("%lld\n", (queryy(n) - queryy(cc)) - cc * (query(n) - query(cc)));
    }
    return 0;
}