#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;
int n, k;
bitset<50005> f, g;
int main()
{
    scanf("%d%d", &n, &k);
    f[0] = 1;
    for (int i = 0; i < min(n, k - 1); ++i)
        f = f ^ (f << (i + 1));
    for (int i = 0; i < k; ++i)
        if (((i + n - 1) | (n - 1)) == (i + n - 1))
            g ^= (f << i);
    for (int i = 0; i < k; ++i)
        printf("%d", (int)g[i]);
    return 0;
}