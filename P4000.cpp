#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
char s[30000005];
int p, mod;
ll n, ans = 1;
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
                    cc.a[i][j] = ((ll)a[i][k] * bb.a[k][j] % mod + cc.a[i][j]) % mod;
        return cc;
    }
};
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    return gcd(y, x % y);
}
int ksm(matrix aa, ll k)
{
    matrix bb;
    bb.a[0][0] = 1;
    bb.a[1][1] = 1;
    while (k)
    {
        if (k & 1)
            bb = bb * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return ((ll)bb.a[0][0] + bb.a[0][1]) % mod;
}
int main()
{
    scanf("%s%d", s, &p);
    mod = p;
    int sqr = sqrt(p);
    for (int i = 2; i <= sqr; ++i)
        if (p % i == 0)
        {
            int k = 0;
            while (p % i == 0)
            {
                ++k;
                p /= i;
            }
            ll tmp;
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
        ll tmp;
        if (p == 2)
            tmp = 3;
        else if (p == 5)
            tmp = 20;
        else
        {
            if (p % 5 == 1 || p % 5 == 4)
                tmp = p - 1;
            else
                tmp = (ll)2 * p + 2;
        }
        ans = ans * tmp / gcd(ans, tmp);
    }
    int len = strlen(s);
    for (int i = 0; i < len; ++i)
        n = (n * 10 + s[i] - '0') % ans;
    if (n == 0)
    {
        printf("0");
        return 0;
    }
    if (n == 1 || n == 2)
    {
        printf("1");
        return 0;
    }
    matrix aa;
    aa.a[0][0] = 1;
    aa.a[0][1] = 1;
    aa.a[1][0] = 1;
    printf("%d", ksm(aa, n - 2));
    return 0;
}