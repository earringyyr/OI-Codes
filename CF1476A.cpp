#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        if (k < n)
            k = ceil((double)n / k) * k;
        printf("%d\n", (int)ceil((double)k / n));
    }
    return 0;
}