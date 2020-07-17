#include <iostream>
#include <cstdio>
using namespace std;
int n;
long long a, b;
long long gcd(long long x, long long y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
int main()
{
    b = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        a = a * (n - i + 1) + b * n;
        b *= n - i + 1;
        long long k = gcd(a, b);
        a /= k;
        b /= k;
    }
    if (b == 1)
    {
        cout << a;
        return 0;
    }
    if (a < b)
    {
        cout << a << endl;
        long long num = b;
        int sum = 0;
        while (num)
        {
            num /= 10;
            ++sum;
        }
        for (int i = 1; i <= sum; ++i)
            cout << "-";
        cout << endl
             << b;
    }
    else
    {
        long long ans = a / b;
        long long num = ans;
        int sum = 0;
        a %= b;
        while (num)
        {
            num /= 10;
            ++sum;
        }
        for (int i = 1; i <= sum; ++i)
            cout << " ";
        cout << a << endl
             << ans;
        long long tot = b, cnt = 0;
        while (tot)
        {
            tot /= 10;
            ++cnt;
        }
        for (int i = 1; i <= cnt; ++i)
            cout << "-";
        cout << endl;
        for (int i = 1; i <= sum; ++i)
            cout << " ";
        cout << b;
    }
    return 0;
}