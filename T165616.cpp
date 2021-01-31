#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
int a[1005][1005], b[1005][1005];
int mp[1005][1005];
void work()
{
    scanf("%d%d", &n, &m);
    if (n == 1 || m == 1)
    {
        puts("Yes");
        return;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            char ch;
            scanf(" %c", &ch);
            a[i][j] = ch - '0';
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            char ch;
            scanf(" %c", &ch);
            b[i][j] = ch - '0';
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            mp[i][j] = a[i][j] ^ b[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = m; j > 1; --j)
            mp[i][j] ^= mp[i][j - 1];
    for (int i = n; i > 1; --i)
        for (int j = 1; j <= m; ++j)
            mp[i][j] ^= mp[i - 1][j];
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            mp[i][j] = mp[i + 1][j + 1];
    --n;
    --m;
    for (int i = n; i > 1; --i)
        for (int j = 1; j < m; ++j)
            mp[i][j] ^= mp[i - 1][j + 1];
    for (int i = n; i > 1; --i)
        for (int j = 2; j <= m; ++j)
            mp[i][j] ^= mp[i - 1][j - 1];
    for (int i = 3; i <= n; ++i)
        for (int j = 2; j < m; ++j)
            if (mp[i][j])
            {
                puts("No");
                return;
            }
    puts("Yes");
    return;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
