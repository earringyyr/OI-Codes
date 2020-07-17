#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
long long n, len, b, sum, a[10000], num[10000];
unsigned long long mi = -1, ans;
int main()
{
    cin >> n >> b;
    for (int i = 2; i <= sqrt(b); ++i)
        if (b % i == 0)
        {
            ++sum;
            a[sum] = i;
            while (b % i == 0)
            {
                b /= i;
                num[sum]++;
            }
        }
    if (b != 1)
    {
        ++sum;
        a[sum] = b;
        num[sum]++;
    }
    len = n;
    for (int i = 1; i <= sum; ++i)
    {
        ans = 0;
        n = len;
        while (n > 0)
        {
            ans += n / a[i];
            n /= a[i];
        }
        if (mi == -1)
            mi = ans / num[i];
        else
            mi = min(mi, ans / num[i]);
    }
    cout << mi;
    return 0;
}