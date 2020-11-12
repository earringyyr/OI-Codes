#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long ll;
int w, mod;
struct complex
{
    int x;
    int y;
    complex(int xx = 0, int yy = 0)
    {
        x = xx;
        y = yy;
    }
    complex operator*(const complex &bb) const
    {
        return complex(((ll)x * bb.x % mod + (ll)y * bb.y % mod * w % mod) % mod, ((ll)x * bb.y % mod + (ll)y * bb.x % mod) % mod);
    }
};
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
int ksm(complex aa, int k)
{
    complex bb(1, 0);
    while (k)
    {
        if (k & 1)
            bb = bb * aa;
        aa = aa * aa;
        k >>= 1;
    }
    return bb.x;
}
int cipolla(int n)
{
    n %= mod;
    if (n == 0)
        return 0;
    if (ksm(n, (mod - 1) / 2) == mod - 1)
        return -1;
    while (1)
    {
        int a = rand() % mod;
        w = ((ll)a * a % mod - n + mod) % mod;
        if (ksm(w, (mod - 1) / 2) != mod - 1)
            continue;
        return ksm(complex(a, 1), (mod + 1) / 2);
    }
}
int main()
{
    srand(time(0));
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d%d", &n, &mod);
        int ans = cipolla(n);
        if (ans > mod - ans)
            ans = mod - ans;
        if (ans == -1)
            puts("Hola!");
        else if (ans == 0)
            puts("0");
        else
            printf("%d %d\n", ans, mod - ans);
    }
    return 0;
}