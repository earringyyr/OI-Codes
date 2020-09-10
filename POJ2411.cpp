#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int h, w;
ll f[2][5005];
int main()
{
    while (scanf("%d%d", &h, &w) == 2)
    {
        if (!h && !w)
            break;
        memset(f, 0, sizeof(f));
        f[1][(1 << w) - 1] = 1;
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
            {
                swap(f[0], f[1]);
                memset(f[1], 0, sizeof(f[1]));
                for (int k = 0; k < (1 << w); ++k)
                {
                    f[1][k ^ (1 << j)] += f[0][k];
                    if (j != 0 && (k & (1 << j)) && !(k & (1 << (j - 1))))
                        f[1][k | (1 << (j - 1))] += f[0][k];
                }
            }
        printf("%lld\n", f[1][(1 << w) - 1]);
    }
    return 0;
}