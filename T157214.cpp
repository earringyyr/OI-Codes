#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int a, b;
ll n;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%d%d", &n, &a, &b);
        if (a > b)
            swap(a, b);
        int tmp = n % (a + b);
        if (tmp >= b)
            puts("1");
        else
        {
            if (tmp / a % 2 == 0)
                puts("0");
            else
                puts("1");
        }
    }
    return 0;
}