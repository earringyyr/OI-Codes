#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, W, ans;
int w[105], v[105];
int num[4], sum[4][105];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int main()
{
    scanf("%d%d", &n, &W);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &w[i], &v[i]);
        ++num[w[i] - w[1]];
        sum[w[i] - w[1]][num[w[i] - w[1]]] = v[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        sort(sum[i] + 1, sum[i] + num[i] + 1, cmp);
        for (int j = 1; j <= num[i]; ++j)
            sum[i][j] = sum[i][j - 1] + sum[i][j];
    }
    for (int i = 0; i <= num[0]; ++i)
        for (int j = 0; j <= num[1]; ++j)
            for (int k = 0; k <= num[2]; ++k)
                for (int l = 0; l <= num[3]; ++l)
                    if ((ll)w[1] * i + (ll)(w[1] + 1) * j + (ll)(w[1] + 2) * k + (ll)(w[1] + 3) * l <= W)
                        ans = max(ans, sum[0][i] + sum[1][j] + sum[2][k] + sum[3][l]);
    printf("%d", ans);
    return 0;
}