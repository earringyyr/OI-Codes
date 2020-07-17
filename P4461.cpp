#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000000
using namespace std;
int m, n, maxn = 2;
struct node
{
    long long a[100005];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    node operator*(const node &bb) const
    {
        node cc;
        cc.a[0] = a[0] + bb.a[0] - 1;
        for (int i = 1; i <= a[0]; ++i)
            for (int j = 1; j <= bb.a[0]; ++j)
            {
                cc.a[i + j - 1] += a[i] * bb.a[j];
                cc.a[i + j] += cc.a[i + j - 1] / mod;
                cc.a[i + j - 1] %= mod;
            }
        for (int i = 1; i <= cc.a[0]; ++i)
        {
            cc.a[i + 1] += cc.a[i] / mod;
            cc.a[i] %= mod;
        }
        if (cc.a[cc.a[0] + 1])
            ++cc.a[0];
        return cc;
    }
    node operator/(int bb) const
    {
        node cc;
        cc.a[0] = a[0];
        for (int i = cc.a[0]; i >= 1; --i)
        {
            cc.a[i] += a[i];
            if (i != 1)
                cc.a[i - 1] += cc.a[i] % bb * mod;
            cc.a[i] /= bb;
        }
        for (int i = cc.a[0]; i >= 1; --i)
            if (!cc.a[i])
                --cc.a[0];
            else
                break;
        return cc;
    }
} a, b;
int main()
{
    scanf("%d", &m);
    while (m--)
    {
        scanf("%d", &n);
        a.a[0] = 1;
        a.a[1] = 2;
        b.a[0] = 1;
        b.a[1] = 1;
        int k = n + 1;
        while (k)
        {
            if (k & 1)
                b = b * a;
            a = a * a;
            k >>= 1;
        }
        b = b / 3;
        for (int i = b.a[0]; i >= 1; --i)
        {
            if (i == b.a[0])
                printf("%lld", b.a[i]);
            else
            {
                if (!(b.a[i] / 100000000))
                    putchar('0');
                if (!(b.a[i] / 10000000))
                    putchar('0');
                if (!(b.a[i] / 1000000))
                    putchar('0');
                if (!(b.a[i] / 100000))
                    putchar('0');
                if (!(b.a[i] / 10000))
                    putchar('0');
                if (!(b.a[i] / 1000))
                    putchar('0');
                if (!(b.a[i] / 100))
                    putchar('0');
                if (!(b.a[i] / 10))
                    putchar('0');
                printf("%lld", b.a[i]);
            }
        }
        putchar('\n');
    }
    return 0;
}