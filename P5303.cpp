#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000007
using namespace std;
int t, n;
struct node
{
    int a[5][5];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator*(node b)
    {
        node c;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                for (int k = 0; k < 5; ++k)
                    c.a[i][j] = ((long long)a[i][k] * b.a[k][j] + c.a[i][j]) % mod;
        return c;
    }
    void init()
    {
        for (int i = 0; i < 5; ++i)
            a[i][i] = 1;
        return;
    }
};
node ksm(node a, int k)
{
    node b;
    b.init();
    while (k)
    {
        if (k % 2 == 1)
            b = b * a;
        a = a * a;
        k /= 2;
    }
    return b;
}
int main()
{
    node a;
    a.a[0][0] = 1;
    a.a[0][1] = 1;
    a.a[0][2] = 2;
    a.a[0][4] = mod - 2;
    a.a[1][0] = 1;
    a.a[2][2] = 1;
    a.a[2][3] = 1;
    a.a[3][2] = 1;
    a.a[4][4] = 1;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        scanf("%d", &n);
        if (n == 1)
        {
            puts("0");
            continue;
        }
        if (n == 2)
        {
            puts("0");
            continue;
        }
        node ans;
        ans.a[2][0] = 2;
        ans.a[3][0] = 1;
        ans.a[4][0] = 1;
        ans = ksm(a, n - 2) * ans;
        printf("%d\n", ans.a[0][0]);
    }
    return 0;
}