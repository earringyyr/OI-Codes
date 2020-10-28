#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, a[105];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        int sum = 0;
        for (int i = 1; i <= n; ++i)
            sum += a[i];
        if (sum == m)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}