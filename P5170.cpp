#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353, inv2 = 499122177, inv6 = 166374059;
struct node
{
    int f;
    int g;
    int h;
};
node solve(int a, int b, int c, int n)
{
    node nxt;
    if (!a)
    {
        nxt.f = (ll)(n + 1) * (b / c) % mod;
        nxt.g = (ll)(n + 1) * (b / c) % mod * (b / c) % mod;
        nxt.h = (ll)n * (n + 1) % mod * inv2 % mod * (b / c) % mod;
        return nxt;
    }
    if (a >= c || b >= c)
    {
        node pre = solve(a % c, b % c, c, n);
        int sum = (ll)n * (n + 1) % mod * inv2 % mod, sum2 = (ll)n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
        int ac = a / c, bc = b / c;
        int ac2 = (ll)ac * ac % mod, bc2 = (ll)bc * bc % mod;
        nxt.f = (((ll)sum * ac % mod + (ll)(n + 1) * bc % mod) % mod + pre.f) % mod;
        nxt.g = ((((((ll)sum2 * ac2 % mod + (ll)(n + 1) * bc2 % mod) % mod + (ll)n * (n + 1) % mod * ac % mod * bc % mod) % mod + (ll)2 * bc * pre.f % mod) % mod + pre.g) % mod + (ll)2 * ac * pre.h % mod) % mod;
        nxt.h = (((ll)sum * bc % mod + (ll)sum2 * ac % mod) % mod + pre.h) % mod;
        return nxt;
    }
    int m = ((ll)a * n + b) / c;
    node pre = solve(c, c - b - 1, a, m - 1);
    nxt.f = ((ll)n * m % mod - pre.f + mod) % mod;
    nxt.g = ((((ll)n * m % mod * (m + 1) % mod - 2 * pre.f % mod + mod) % mod - 2 * pre.h % mod + mod) % mod - nxt.f + mod) % mod;
    nxt.h = (ll)inv2 * ((((ll)m * n % mod * (n + 1) % mod - pre.f + mod) % mod - pre.g + mod) % mod) % mod;
    return nxt;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, a, b, c;
        scanf("%d%d%d%d", &n, &a, &b, &c);
        node tmp = solve(a, b, c, n);
        printf("%d %d %d\n", tmp.f, tmp.g, tmp.h);
    }
    return 0;
}