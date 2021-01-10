#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, ans;
int h[5005];
int f[5005][5005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &h[i]);
    for (int i = 1; i <= n; ++i)
    {
        int minx = 0x7fffffff, lst = i, sum = 1;
        f[i][i] = 1;
        ans ^= f[i][i];
        for (int j = i - 1; j >= 1; --j)
        {
            int k = (h[i] - h[j]) / (i - j);
            if (k < minx)
                sum += min(f[j + 1][lst - 1], f[j + 1][lst]);
            if (k < minx)
                lst = j;
            f[j][i] = sum + min(f[j][lst - 1], f[j][lst]);
            minx = min(minx, k);
            ans ^= f[j][i];
        }
    }
    printf("%d", ans);
    return 0;
}