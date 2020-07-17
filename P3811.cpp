#include <iostream>
#include <cstdio>
using namespace std;
int n, p, inv[3000005];
int main()
{
    scanf("%d%d", &n, &p);
    inv[1] = 1;
    printf("%d\n", inv[1]);
    for (int i = 2; i <= n; ++i)
    {
        inv[i] = ((long long)(p - p / i) * inv[p % i]) % p;
        printf("%d\n", inv[i]);
    }
    return 0;
}