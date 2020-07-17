#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, a[1005];
double num;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 2; i < n; ++i)
        num += a[i];
    num /= (n - 2);
    printf("%.2f", num);
    return 0;
}