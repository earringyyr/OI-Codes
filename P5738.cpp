#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
double maxn, num;
int a[25], n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cin >> a[j];
        sort(a + 1, a + m + 1);
        num = 0;
        for (int j = 2; j < m; ++j)
            num += a[j];
        num /= m - 2;
        maxn = max(maxn, num);
    }
    printf("%.2f", maxn);
    return 0;
}