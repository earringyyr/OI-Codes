#include <iostream>
#include <cstdio>
using namespace std;
int ksm(int a, int k, int mod)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (long long)b * a % mod;
        a = (long long)a * a % mod;
        k >>= 1;
    }
    return b;
}
int main()
{
    int n, m, k, x;
    scanf("%d%d%d%d", &n, &m, &k, &x);
    k = ksm(10, k, n);
    for (int i = 1; i <= k; ++i)
        x = (x + m) % n;
    cout << x;
    return 0;
}