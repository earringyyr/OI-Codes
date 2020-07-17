#include <iostream>
#include <cstdio>
using namespace std;
int n, m, top, num[3005], h[3005], s[3005], a[3005][3005];
long long ans;
char c[3005];
int main()
{
    scanf("%d%d", &n);
    m = n;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", c + 1);
        for (int j = 1; j <= m; ++j)
        {
            if (c[j] == 'B')
                a[i][j] = 0;
            else
                a[i][j] = 1;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        top = 0;
        for (int j = 1; j <= m; ++j)
        {
            if (!a[i][j])
                h[j] = i;
            while (top && h[s[top]] < h[j])
                --top;
            s[++top] = j;
            num[top] = num[top - 1] + (i - h[s[top]]) * (s[top] - s[top - 1]);
            ans += num[top];
        }
    }
    printf("%lld", ans);
    return 0;
}