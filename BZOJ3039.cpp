#include <iostream>
#include <cstdio>
using namespace std;
int n, m, top, ans, len[1005][1005], st[1005][2];
char s[1005][1005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf(" %c", &s[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] == 'F')
                len[i][j] = len[i - 1][j] + 1;
            else
                len[i][j] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int num = 0;
            while (top > 0 && st[top][0] >= len[i][j])
            {
                num += st[top][1];
                ans = max(ans, st[top][0] * num);
                --top;
            }
            ++top;
            st[top][0] = len[i][j];
            st[top][1] = num + 1;
        }
        int num = 0;
        while (top > 0)
        {
            num += st[top][1];
            ans = max(ans, st[top][0] * num);
            --top;
        }
    }
    printf("%d", ans * 3);
    return 0;
}