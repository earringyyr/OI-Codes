#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, num;
ll w[2000005][2], f[2000005][2];
int main()
{
    scanf("%d", &n);
    num = 1 << n;
    for (int i = 0; i < num; ++i)
        scanf("%lld", &w[i][0]);
    for (int i = 0; i < num; ++i)
        scanf("%lld", &w[i][1]);
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                w[j + mid + k][0] += w[j + k][0];
                w[j + mid + k][1] += w[j + k][1];
            }
    for (int i = 0; i < num; ++i)
    {
        f[i][0] = w[i][0];
        f[i][1] = w[i][1];
        for (int j = 0; j < n; ++j)
            if (i & (1 << j))
            {
                f[i][0] = min(f[i][0], f[i ^ (1 << j)][0] + w[i][0] - w[i ^ (1 << j)][0]);
                f[i][0] = min(f[i][0], f[i ^ (1 << j)][1] + w[i][0] - w[i ^ (1 << j)][0]);
                f[i][1] = min(f[i][1], f[i ^ (1 << j)][0] + w[i][1] - w[i ^ (1 << j)][1]);
                f[i][1] = min(f[i][1], f[i ^ (1 << j)][1] + w[i][1] - w[i ^ (1 << j)][1]);
            }
    }
    printf("%lld", min(f[num - 1][0], f[num - 1][1]));
    return 0;
}