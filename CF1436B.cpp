#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                if (i == j || j == i + 1 || (i == n && j == 1))
                    printf("1 ");
                else
                    printf("0 ");
            putchar('\n');
        }
    }
    return 0;
}