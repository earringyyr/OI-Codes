#include <iostream>
#include <cstdio>
using namespace std;
int s, sum, f[1005];
int main()
{
    scanf("%d", &s);
    for (int i = 1; i <= s; ++i)
    {
        sum = 0;
        for (int j = 1; j < i; ++j)
            if (i % j == 0)
                sum += j;
        for (int j = s; j >= i; --j)
            f[j] = max(f[j], f[j - i] + sum);
    }
    printf("%d", f[s]);
    return 0;
}