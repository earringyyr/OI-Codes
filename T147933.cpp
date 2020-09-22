#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int ksm(int a, int k, int mod)
{
    int b = 1;
    while (k)
    {
        if (k & 1)
            b = (ll)b * a % mod;
        a = (ll)a * a % mod;
        k >>= 1;
    }
    return b;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a, b, c, k;
        scanf("%d%d%d%d", &a, &b, &c, &k);
        printf("%d\n", (int)((ll)c * ksm(2, k, a + b + c) % (a + b + c)));
    }
    return 0;
}