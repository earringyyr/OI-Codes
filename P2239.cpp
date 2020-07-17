#include <iostream>
#include <cstdio>
using namespace std;
int calc(int n, int i, int j)
{
    if (i == 1)
        return j;
    if (i == n)
        return 3 * n - j - 1;
    if (j == 1)
        return 4 * n - i - 2;
    if (j == n)
        return n + i - 1;
    return calc(n - 2, i - 1, j - 1) + 4 * (n - 1);
}
int main()
{
    int n, i, j;
    scanf("%d%d%d", &n, &i, &j);
    printf("%d", calc(n, i, j));
    return 0;
}