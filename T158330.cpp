#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, lst, f[15][10];
void solve(int K)
{
    memset(f, 0, sizeof(f));
    for (int i = 0; i < 10; ++i)
        f[1][i] = 1;
    for (int i = 2; i <= K; ++i)
        for (int j = 0; j < 10; ++j)
            for (int k = max(0, j - 1); k <= min(9, j + 1); ++k)
                f[i][k] += f[i - 1][j];
    for (int i = 1; i < 10; ++i)
        if (f[K][i] >= n)
        {
            lst = i;
            printf("%d", lst);
            for (int j = K - 1; j >= 1; --j)
                for (int k = max(0, lst - 1); k <= min(9, lst + 1); ++k)
                    if (f[j][k] >= n)
                    {
                        lst = k;
                        printf("%d", lst);
                        break;
                    }
                    else
                        n -= f[j][k];
            exit(0);
        }
        else
            n -= f[K][i];
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 10; ++i)
        solve(i);
    return 0;
}