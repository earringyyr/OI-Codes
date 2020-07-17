#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k, a[5000005];
int qsort(int l, int r)
{
    int i = l, j = r, mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[j] > mid)
            --j;
        while (a[i] < mid)
            ++i;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (k <= j)
        return qsort(l, j);
    if (i <= k)
        return qsort(i, r);
    return a[j + 1];
}
int main()
{
    cin >> n >> k;
    ++k;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    cout << qsort(1, n);
    return 0;
}