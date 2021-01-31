#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, maxn, cnt;
int a[105];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        maxn = 1;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        cnt = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (a[i] == a[i - 1])
                ++cnt;
            else
            {
                maxn = max(maxn, cnt);
                cnt = 1;
            }
        }
        maxn = max(maxn, cnt);
        printf("%d\n", maxn);
    }
    return 0;
}