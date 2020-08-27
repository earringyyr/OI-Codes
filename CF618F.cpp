#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, type;
int pos[1000005][2];
ll a[1000005], b[1000005];
int main()
{
    memset(pos, -1, sizeof(pos));
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &b[i]);
        b[i] += b[i - 1];
    }
    if (a[n] > b[n])
    {
        type = 1;
        for (int i = 1; i <= n; ++i)
            swap(a[i], b[i]);
    }
    pos[0][0] = 0;
    pos[0][1] = 0;
    int jj = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (jj < n && a[i] >= b[jj + 1])
            ++jj;
        int k = a[i] - b[jj];
        if (pos[k][0] != -1)
        {
            if (!type)
            {
                printf("%d\n", i - pos[k][0]);
                for (int j = pos[k][0] + 1; j <= i; ++j)
                    printf("%d ", j);
                printf("\n%d\n", jj - pos[k][1]);
                for (int j = pos[k][1] + 1; j <= jj; ++j)
                    printf("%d ", j);
            }
            else
            {
                printf("%d\n", jj - pos[k][1]);
                for (int j = pos[k][1] + 1; j <= jj; ++j)
                    printf("%d ", j);
                printf("\n%d\n", i - pos[k][0]);
                for (int j = pos[k][0] + 1; j <= i; ++j)
                    printf("%d ", j);
            }
            return 0;
        }
        pos[k][0] = i;
        pos[k][1] = jj;
    }
    return 0;
}