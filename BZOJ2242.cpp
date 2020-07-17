#include <iostream>
#include <cstdio>
#include <cmath>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
int x, y;
unordered_map<int, int> hsh;
int ksm(int a, int b, int mod)
{
    int c = 1;
    while (b)
    {
        if (b & 1)
            c = (long long)c * a % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }
    return c;
}
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
void exgcd(int a, int b)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return;
}
int main()
{
    int T, k;
    scanf("%d%d", &T, &k);
    while (T--)
    {
        int y, z, p;
        scanf("%d%d%d", &y, &z, &p);
        if (k == 1)
            printf("%d\n", ksm(y, z, p));
        if (k == 2)
            if (z % gcd(y, p) != 0)
                puts("Orz, I cannot find x!");
            else
            {
                exgcd(y, p);
                x = ((long long)x * z % p + p) % p;
                printf("%d\n", x);
            }
        if (k == 3)
        {
            y %= p;
            z %= p;
            if (!y && z)
                puts("Orz, I cannot find x!");
            else if (!y && !z)
                puts("1");
            else if (z == 1)
                puts("0");
            else
            {
                int m = ceil(sqrt(p)), num = z % p, sum = ksm(y, m, p);
                hsh.clear();
                for (int i = 1; i <= m; ++i)
                {
                    num = (long long)num * y % p;
                    hsh[num] = i;
                }
                num = 1;
                bool fla = false;
                for (int i = 1; i <= m; ++i)
                {
                    num = (long long)num * sum % p;
                    if (hsh[num])
                    {
                        printf("%d\n", ((i * m - hsh[num]) % p + p) % p);
                        fla = true;
                        break;
                    }
                }
                if (!fla)
                    puts("Orz, I cannot find x!");
            }
        }
    }
    return 0;
}