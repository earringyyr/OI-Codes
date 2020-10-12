#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
char s[30000005];
int n, p, mod, ans;
struct matrix
{
    int a[2][2];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                {
                    cc.a[i][j] += (ll)a[i][k] * bb.a[k][j] % mod;
                    cc.a[i][j] %= mod;
                }
        return cc;
    }
};
int gcd(int x, int y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int main()
{
    scanf("%s%d", s, &p);
    mod = p;
    matrix a, b, c;
    c = a * b;
    int sqr = sqrt(mod);
    for (int i = 2; i <= sqr; ++i)
        if (mod % i == 0)
        {
            int k = 0;
            while (mod % i == 0)
            {
                ++k;
                p /= i;
            }
            int tmp;
            if (i == 2)
                tmp = 3;
            else if (i == 5)
                tmp = 20;
            else
            {
                if (i % 5 == 1 || i % 5 == 4)
                    tmp = i - 1;
                else
                    tmp = 2 * i + 2;
            }
            for (int j = 1; j < k; ++j)
                tmp = tmp * i;
            ans = ans * tmp / gcd(ans, tmp);
        }
    if (p > 1)
    {
        int tmp;
        if (p == 2)
            tmp = 3;
        else if (p == 5)
            tmp = 20 else
            {
                if (p % 5 == 1 || p % 5 == 4)
                    tmp = p - 1;
                else
                    tmp = 2 * p + 2;
            }
        ans = ans * tmp / gcd(ans, tmp);
    }
    return 0;
}