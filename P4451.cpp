#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007, sqr2 = 59713600;
char s[10005];
int ans;
struct node
{
    int a[10005];
    node()
    {
        memset(a, 0, sizeof(a));
    }
    void div()
    {
        for (int i = a[0]; i >= 1; --i)
        {
            if (i != 1)
                a[i - 1] += a[i] % 2 * 10;
            a[i] /= 2;
        }
        while (a[0] && !a[a[0]])
            --a[0];
        return;
    }
} n;
int ksm(int aa, node k)
{
    int bb = 1;
    while (k.a[0])
    {
        if (k.a[1] & 1 == 1)
            bb = (ll)aa * bb % mod;
        aa = (ll)aa * aa % mod;
        k.div();
    }
    return bb;
}
int main()
{
    scanf("%s", s + 1);
    n.a[0] = strlen(s + 1);
    for (int i = 1; i <= n.a[0]; ++i)
        n.a[i] = s[n.a[0] - i + 1] - '0';
    ans = (ll)sqr2 / 4 * (ksm(1 + sqr2, n) - ksm(1 - sqr2 + mod, n) + mod) % mod;
    printf("%d", ans);
    return 0;
}