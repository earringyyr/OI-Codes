#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    if (n % 2 == 0)
    {
        printf("NO");
        return 0;
    }
    printf("YES\n");
    for (int i = 1; i <= 2 * n; ++i)
        if (i <= n)
        {
            if (i % 2 == 1)
                printf("%d ", 2 * i - 1);
            else
                printf("%d ", 2 * i);
        }
        else
        {
            if ((i - n) % 2 == 1)
                printf("%d ", 2 * (i - n));
            else
                printf("%d ", 2 * (i - n) - 1);
        }
    return 0;
}