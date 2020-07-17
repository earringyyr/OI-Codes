#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, mod;
struct node
{
    int a[2][2];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator*(const node &bb) const
    {
        node cc;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    cc.a[i][j] = (cc.a[i][j] + (long long)a[i][k] * bb.a[k][j] % mod) % mod;
        return cc;
    }
};
node ksm(node a, int k)
{
    node b;
    b.a[0][0] = 1;
    b.a[1][1] = 1;
    while (k)
    {
        if (k & 1)
            b = b * a;
        a = a * a;
        k >>= 1;
    }
    return b;
}
int main()
{
    scanf("%d%d", &n, &mod);
    node a;
    a.a[0][0] = 1;
    a.a[0][1] = 1;
    a.a[1][0] = 1;
    a = ksm(a, n - 2);
    printf("%d", (a.a[0][0] + a.a[0][1]) % mod);
    return 0;
}