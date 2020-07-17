#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = max(2, n); i <= m; ++i)
        {
            int p = true;
            for (int j = 2; j <= sqrt(i); ++j)
                if (i % j == 0)
                {
                    p = false;
                    break;
                }
            if (p)
                printf("%d\n", i);
        }
        printf("\n");
    }
    return 0;
}