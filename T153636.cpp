#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, num, ans = 1, a[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if (a[i] - a[i - 1] > 2)
            a[i] = a[i - 1] + 2;
        if (i == 1)
            a[i] = 1;
        ans = (ll)ans * (i - num) % mod;
        if (i != 1 && a[i] - a[i - 1] == 1)
        {
            a[i] = a[i - 1];
            ++num;
        }
    }
    printf("%d", ans);
    return 0;
}