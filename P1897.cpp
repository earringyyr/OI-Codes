#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n, num, tim, a[100005];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    num = unique(a + 1, a + n + 1) - a - 1;
    tim = a[num] * (4 + 6) + n;
    if (!a[1])
        tim += 5 * (num - 1);
    else
        tim += 5 * num;
    printf("%d", tim);
    return 0;
}