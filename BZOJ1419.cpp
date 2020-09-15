#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int r, b;
double f[2][5005];
int main()
{
    scanf("%d%d", &r, &b);
    for (int i = 1; i <= r; ++i)
    {
        f[i & 1][0] = i;
        for (int j = 1; j <= b; ++j)
        {
            f[i & 1][j] = (f[i & 1 ^ 1][j] + 1) * ((double)i / (i + j)) + (f[i & 1][j - 1] - 1) * ((double)j / (i + j));
            if (f[i & 1][j] < 0)
                f[i & 1][j] = 0;
        }
    }
    printf("%.6f", f[r & 1][b] - 0.0000005);
    return 0;
}