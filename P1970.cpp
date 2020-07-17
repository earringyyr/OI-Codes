#include <iostream>
#include <cstdio>
using namespace std;
int n, h[100005], ans, type = -1;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &h[i]);
    for (int i = 1; i <= n; ++i)
    {
        if (i == 1 || i == n)
            ++ans;
        else
        {
            if (h[i] > h[i - 1])
                type = 1;
            if (h[i] < h[i - 1])
                type = 0;
            if (type == 0 && h[i] < h[i + 1])
                ++ans;
            if (type == 1 && h[i] > h[i + 1])
                ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}