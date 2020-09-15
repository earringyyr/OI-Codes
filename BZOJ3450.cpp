#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
double f[300005], d[300005];
char s[300005];
int main()
{
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; ++i)
        if (s[i] == 'o')
        {
            d[i] = d[i - 1] + 1;
            f[i] = f[i - 1] + 2 * d[i - 1] + 1;
        }
        else if (s[i] == 'x')
        {
            d[i] = 0;
            f[i] = f[i - 1];
        }
        else
        {
            f[i] = f[i - 1] + (2 * d[i - 1] + 1) / 2;
            d[i] = (d[i - 1] + 1) / 2;
        }
    printf("%.4f", f[n]);
    return 0;
}