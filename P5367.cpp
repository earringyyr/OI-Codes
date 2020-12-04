#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, ans = 1;
int a[1000005], fac[1000005], c[1000005];
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
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (ll)fac[i - 1] * i % mod;
    for (int i = 1; i <= n; ++i)
    {
        ans = (ans + (ll)(a[i] - 1 - ask(a[i])) * fac[n - i] % mod) % mod;
        add(a[i], 1);
    }
    printf("%d\n", ans);
    return 0;
}