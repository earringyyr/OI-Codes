#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, ans, num, num1, num2, a[500005], b[500005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    for (int i = n; i >= 1; --i)
    {
        num = ((((ll)a[i] * b[i] % mod * (n - i + 1) % mod + (ll)num1 * b[i] % mod) % mod + (ll)num2 * a[i] % mod) % mod + num) % mod;
        num1 = (num1 + (ll)a[i] * (n - i + 1) % mod) % mod;
        num2 = (num2 + (ll)b[i] * (n - i + 1) % mod) % mod;
        ans = (ans + num) % mod;
    }
    printf("%d", ans);
    return 0;
}