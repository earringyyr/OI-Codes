#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n;
char s[300005];
struct matrix
{
    int a[4][4];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator*(const matrix &bb) const
    {
        matrix cc;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < 4; ++k)
                    cc.a[i][j] = (cc.a[i][j] + (ll)a[i][k] * bb.a[k][j] % mod) % mod;
        return cc;
    }
} add, sub, mul, num[10];
matrix ksm(matrix aa, ll k)
{
    matrix bb;
    for (int i = 0; i < 4; ++i)
        bb.a[i][i] = 1;
    while (k)
    {
        if (k & 1)
            bb = bb * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return bb;
}
int main()
{
    add.a[0][0] = 1;
    add.a[0][2] = 1;
    add.a[1][3] = 1;
    add.a[3][3] = 1;
    sub.a[0][0] = 1;
    sub.a[0][2] = 1;
    sub.a[1][3] = mod - 1;
    sub.a[3][3] = 1;
    mul.a[0][0] = 1;
    mul.a[1][2] = 1;
    mul.a[3][3] = 1;
    for (int i = 0; i < 10; ++i)
    {
        num[i].a[0][0] = 1;
        num[i].a[1][1] = 1;
        num[i].a[2][1] = i;
        num[i].a[2][2] = 10;
        num[i].a[3][3] = 1;
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        matrix ans;
        for (int i = 0; i < 4; ++i)
            ans.a[i][i] = 1;
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i)
            if (s[i] == '+')
                ans = add * ans;
            else if (s[i] == '-')
                ans = sub * ans;
            else if (s[i] == '*')
                ans = mul * ans;
            else if (s[i] == '(')
            {
                matrix tmp;
                for (int j = 0; j < 4; ++j)
                    tmp.a[j][j] = 1;
                int j = i + 1;
                while (s[j] != ')')
                {
                    if (s[j] == '+')
                        tmp = add * tmp;
                    else if (s[j] == '-')
                        tmp = sub * tmp;
                    else if (s[j] == '*')
                        tmp = mul * tmp;
                    else
                        tmp = num[s[j] - '0'] * tmp;
                    ++j;
                }
                j += 3;
                ll k = 0;
                while (s[j] != ')')
                {
                    k = k * 10 + s[j] - '0';
                    ++j;
                }
                ans = ksm(tmp, k) * ans;
                i = j;
            }
            else
                ans = num[s[i] - '0'] * ans;
        printf("%d\n", ((ans.a[0][1] + ans.a[0][3]) % mod + (ans.a[2][1] + ans.a[2][3]) % mod) % mod);
    }
    return 0;
}