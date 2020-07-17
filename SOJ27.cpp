#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int n, a[100005], c[100005];
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
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    int ans = 0;
    for (int i = n; i >= 1; --i)
    {
        ans += query(a[i] - 1);
        add(a[i], 1);
    }
    printf("%lld", ans);
    return 0;
}