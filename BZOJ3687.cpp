#include <iostream>
#include <cstdio>
#include <bitset>
using namespace std;
int n, sum, ans;
bitset<2000005> s;
int main()
{
    scanf("%d", &n);
    s[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        sum += x;
        s ^= (s << x);
    }
    for (int i = 1; i <= sum; ++i)
        if (s[i])
            ans ^= i;
    printf("%d", ans);
    return 0;
}