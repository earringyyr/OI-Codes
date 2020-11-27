#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, f[55][55];
char s[55];
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int len = 1; len <= n; ++len)
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1;
            if (s[i] == s[j])
            {
                f[i][j] = f[i + 1][j - 1] + 1;
                for (int k = i + 1; k < j; ++k)
                    if (s[k] == s[i])
                        f[i][j] = min(f[i][j], f[i][k] + f[k][j] - 1);
            }
            else
            {
                f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
                for (int k = i + 1; k < j; ++k)
                    if (s[k] == s[i] || s[k] == s[j])
                        f[i][j] = min(f[i][j], f[i][k] + f[k][j] - 1);
            }
        }
    printf("%d", f[1][n]);
    return 0;
}