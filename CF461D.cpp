#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int n, k, cnt;
int fa[200005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void link(int x, int y)
{
    x = getfather(x);
    y = getfather(y);
    if (x != y)
        fa[x] = y;
    return;
}
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)bb * aa % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 2 * (n + 2); ++i)
        fa[i] = i;
    for (int i = 1; i <= k; ++i)
    {
        int x, y;
        char ch;
        scanf("%d%d %c", &x, &y, &ch);
        int l = y - x + 1, r = y + x - 1;
        if (l < 1)
            l = 2 - l;
        if (r > n)
            r = 2 * n - r;
        r += 2;
        if (ch == 'x')
        {
            link(l, r);
            link(l + n + 2, r + n + 2);
        }
        else
        {
            link(l, r + n + 2);
            link(l + n + 2, r);
        }
    }
    for (int i = 1; i <= n + 2; ++i)
    {
        if (getfather(i) == getfather(i + n + 2))
        {
            printf("0");
            return 0;
        }
        if (getfather(i) == i)
            ++cnt;
        if (getfather(i + n + 2) == i + n + 2)
            ++cnt;
    }
    printf("%d", ksm(2, (cnt / 2 - 2)));
    return 0;
}