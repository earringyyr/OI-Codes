#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a[5];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 1; i <= 4; ++i)
            scanf("%lld", &a[i]);
        sort(a + 1, a + 5);
        if (a[1] + a[4] != a[2] + a[3])
            puts("0");
        else
        {
            int ans = 8;
            if (a[1] == a[4])
                ans = 4;
            if (a[2] == a[3])
                ans = 4;
            if (a[1] == a[2] && a[3] == a[4])
                ans = 4;
            if (a[1] == a[4] && a[2] == a[3])
                ans = 1;
            printf("%d\n", ans);
        }
    }
    return 0;
}