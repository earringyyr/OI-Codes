#include <iostream>
#include <cstdio>
#define mod 1000000007
using namespace std;
int n, k;
int ksm(int a, long long c)
{
    int b = 1;
    while (c)
    {
        if (c & 1)
            b = (long long)b * a % mod;
        a = (long long)a * a % mod;
        c >>= 1;
    }
    return b;
}
int main()
{
    scanf("%d%d", &n, &k);
    printf("%d", ksm(2, (long long)n * k));
    return 0;
}
