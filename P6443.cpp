#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int m, n, k, ans;
int main()
{
    scanf("%d%d%d", &m, &n, &k);
    if (m % 2 == 1)
    {
        --m;
        --k;
    }
    if (2 * n < m)
        k -= m - 2 * n;
    else
    {
        k -= n - m / 2;
        n = m / 2;
    }
    ans = n;
    if (k > 0)
        ans -= ceil((double)k / 3);
    printf("%d", ans);
    return 0;
}