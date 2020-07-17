#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define mod 10000
long long n, k, a[3][3], b[3][3], c[3][3];
void ksm()
{
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= 2; ++i)
        b[i][i] = 1;
    while (k > 0)
    {
        if (k % 2 == 1)
        {
            memset(c, 0, sizeof(c));
            for (int i = 1; i <= 2; ++i)
                for (int j = 1; j <= 2; ++j)
                    for (int kk = 1; kk <= 2; ++kk)
                    {
                        c[i][j] += (a[i][kk] * b[kk][j]) % mod;
                        c[i][j] %= mod;
                    }
            for (int i = 1; i <= 2; ++i)
                for (int j = 1; j <= 2; ++j)
                    b[i][j] = c[i][j];
        }
        k /= 2;
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                for (int kk = 1; kk <= 2; ++kk)
                {
                    c[i][j] += (a[i][kk] * a[kk][j]) % mod;
                    c[i][j] %= mod;
                }
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                a[i][j] = c[i][j];
    }
    return;
}
int main()
{
    while (cin >> n)
    {
        if (n == -1)
            break;
        if (n == 0)
        {
            cout << 0 << endl;
            continue;
        }
        if (n == 1)
        {
            cout << 1 << endl;
            continue;
        }
        if (n == 2)
        {
            cout << 1 << endl;
            continue;
        }
        k = n - 2;
        a[1][1] = 1;
        a[1][2] = 1;
        a[2][1] = 1;
        a[2][2] = 0;
        ksm();
        cout << (b[1][1] + b[1][2]) % mod << endl;
    }
    return 0;
}