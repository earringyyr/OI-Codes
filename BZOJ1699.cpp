#include <iostream>
#include <cstdio>
using namespace std;
int n, q, h[50005], lg[50005], a[50005][30], b[50005][30];
int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &h[i]);
        a[i][0] = h[i];
        b[i][0] = h[i];
        lg[i] = lg[i - 1] + (1 << (lg[i - 1] + 1) == i ? 1 : 0);
    }
    for (int i = n; i >= 1; --i)
        for (int j = 1; j <= lg[n - i + 1]; ++j)
        {
            a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
            b[i][j] = min(b[i][j - 1], b[i + (1 << (j - 1))][j - 1]);
        }
    for (int i = 1; i <= q; ++i)
    {
        int aa, bb;
        scanf("%d%d", &aa, &bb);
        int k = lg[bb - aa + 1];
        int ans1, ans2;
        ans1 = max(a[aa][k], a[bb - (1 << k) + 1][k]);
        ans2 = min(b[aa][k], b[bb - (1 << k) + 1][k]);
        printf("%d\n", ans1 - ans2);
    }
    return 0;
}