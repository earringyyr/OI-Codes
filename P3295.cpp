#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 1000000007;
int n, m, lg[100005];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= m; ++i)
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (l1 > l2)
        {
            swap(l1, l2);
            swap(r1, r2);
        }
    }
    return 0;
}