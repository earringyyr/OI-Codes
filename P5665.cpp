#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int mod = 1 << 30;
int n, type, a[40000005], b[40000005];
int main()
{
    scanf("%d%d", &n, &type);
    if (type == 0)
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
    else
    {
        int x, y, z, m;
        scanf("%d%d%d%d%d%d", &x, &y, &z, &b[1], &b[2], &m);
        for (int i = 3; i <= n; ++i)
            b[i] = ((ll)b[i - 1] * x + (ll)b[i - 2] * y + z) % mod;
        int j = 1;
        for (int i = 1; i <= m; ++i)
        {
            int p, l, r;
            scanf("%d%d%d", &p, &l, &r);
            for (j; j <= p; ++j)
                a[i] = b[i] % (r - l + 1) + l;
        }
    }
    
    return 0;
}