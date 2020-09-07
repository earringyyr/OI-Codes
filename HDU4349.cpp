#include <iostream>
#include <cstdio>
using namespace std;
int n, sum;
int main()
{
    while (scanf("%d", &n) == 1)
    {
        sum = 0;
        while (n)
        {
            if (n & 1)
                ++sum;
            n >>= 1;
        }
        printf("%d\n", 1 << sum);
    }
    return 0;
}