#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, u, k;
double f[600005][10];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &u, &k);
        for (int i = 1; i <= min(n, 6 * k); ++i)
        {
            f[i][1] = max(1.0 * k + 1, f[i - 1][0] + 1);
            f[i][2] = max(2.0 * k + 1, f[i - 1][0] + 1);
            f[i][3] = max(3.0 * k + 1, f[i - 1][0] + 1);
            f[i][4] = max(4.0 * k + 1, f[i - 1][0] + 1);
            f[i][5] = max(5.0 * k + 1, f[i - 1][0] + 1);
            f[i][6] = max(6.0 * k + 1, f[i - 1][0] + 1);
            f[i][0] = (f[i][1] + f[i][2] + f[i][3] + f[i][4] + f[i][5] + f[i][6]) / 6;
            if (f[i][0] >= 6 * k)
            {
                if (6 * k >= n)
                    f[n][0] = n - i + f[i][0];
                else
                    f[6 * k][0] = 6 * k - i + f[i][0];
                break;
            }
        }
        if (6 * k >= n)
            printf("%.10f\n", max((double)u * k, f[n][0]));
        else
            printf("%.10f\n", f[6 * k][0] + n - 6 * k);
    }
    return 0;
}