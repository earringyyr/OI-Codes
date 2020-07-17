#include <iostream>
#include <cstdio>
#define mod 19260817
using namespace std;
int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        x %= mod;
        c = getchar();
    }
    return x;
}
int ksm(int a, int b)
{
    int x = 1;
    while (b)
    {
        if (b & 1)
            x = (long long)x * a % mod;
        a = (long long)a * a % mod;
        b >>= 1;
    }
    return x;
}
int main()
{
    int a = read(), b = read();
    if (b == 0)
        puts("Angry!");
    else
        printf("%d", (long long)a * ksm(b, mod - 2) % mod);
    return 0;
}