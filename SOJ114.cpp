#include <iostream>
#include <cstdio>
using namespace std;
int n, len, a[1000005], b[1000005];
int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= n; ++i)
    {
        if (a[i] >= b[len])
        {
            b[++len] = a[i];
            continue;
        }
        int l = 0, r = len;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (a[i] >= b[mid])
                l = mid + 1;
            else
                r = mid;
        }
        b[l] = a[i];
    }
    printf("%d", n - len);
    return 0;
}