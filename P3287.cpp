#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, k, ans, a[10005], f[10005][505];
struct BIT1
{
    int c[505];
    int lowbit(int x)
    {
        return x & -x;
    }
    void add(int x, int val)
    {
        while (x <= k + 1)
        {
            c[x] = max(c[x], val);
            x += lowbit(x);
        }
        return;
    }
    int ask(int x)
    {
        int num = 0;
        while (x >= 1)
        {
            num = max(num, c[x]);
            x -= lowbit(x);
        }
        return num;
    }
} bit1[5505];
struct BIT2
{
    int c[5005];
    int lowbit(int x)
    {
        return x & -x;
    }
    void add(int x, int val)
    {
        while (x <= 5000)
        {
            c[x] = max(c[x], val);
            x += lowbit(x);
        }
        return;
    }
    int ask(int x)
    {
        int num = 0;
        while (x >= 1)
        {
            num = max(num, c[x]);
            x -= lowbit(x);
        }
        return num;
    }
} bit2[505];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        for (int j = 0; j <= k; ++j)
        {
            f[i][j] = max(bit1[a[i] + j].ask(j + 1), bit2[j].ask(a[i])) + 1;
            ans = max(ans, f[i][j]);
            bit1[a[i] + j].add(j + 1, f[i][j]);
            bit2[j].add(a[i], f[i][j]);
        }
    }
    printf("%d", ans);
    return 0;
}