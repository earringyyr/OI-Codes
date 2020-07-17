#include <iostream>
#include <cstdio>
using namespace std;
#define mod 1000000007
int n, m;
long long ksm(long long a, int b)
{
    long long ans = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            ans = (ans * a) % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    if (n > m)
        swap(n, m);
    if (n == 1)
        cout << ksm(2, m);
    else if (n == 2)
        cout << 4 * ksm(3, m - 1) % mod;
    else if (n == 3)
        cout << 112 * ksm(3, m - 3) % mod;
    else if (n == m)
        cout << (83 * ksm(8, n) % mod + 5 * ksm(2, n + 7) % mod) * 190104168 % mod;
    else
        cout << (83 * ksm(8, n) % mod + ksm(2, n + 8)) % mod * ksm(3, m - n - 1) % mod * 570312504 % mod;
    return 0;
}