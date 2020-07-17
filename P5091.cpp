#include <iostream>
#include <cstdio>
using namespace std;
int a, b, m, mm, sum, ans = 1, phi, p;
int read()
{
    char c = getchar();
    long long x = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + c - 48;
        if (x >= phi)
            p = 1;
        x %= phi;
        c = getchar();
    }
    return x;
}
int main()
{
    scanf("%d%d", &a, &m);
    phi = m;
    mm = m;
    for (int i = 2; i * i <= m; ++i)
        if (mm % i == 0)
        {
            phi = (long long)phi * (i - 1) / i;
            while (mm % i == 0)
                mm /= i;
        }
    if (mm > 1)
        phi = (long long)phi * (mm - 1) / mm;
    b = read();
    if (p)
        b += phi;
    for (int i = 1; i <= b; ++i)
        ans = ((long long)ans * a) % m;
    cout << ans;
    return 0;
}