#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, f[100005];
int main()
{
    scanf("%d%d", &n, &k);
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        f[i] = f[i - 1];
        if (i > k)
            f[i] += f[i - k - 1];
        else
            ++f[i];
        f[i] %= 5000011;
    }
    printf("%d", f[n]);
    return 0;
}