#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int h, n, num;
int f[20005];
struct node
{
    int a;
    int b;
} w[10005];
int main()
{
    scanf("%d%d", &h, &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &w[i].a, &w[i].b);
    for (int i = 1; i <= h; ++i)
        f[i + 10000] = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= h; ++j)
            f[j + 10000] = min(f[j + 10000], f[j - w[i].a + 10000] + w[i].b);
    printf("%d", f[h + 10000]);
    return 0;
}