#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int f[4005], c[4005][4005];
class SumOverPermutations
{
public:
    int findSum(int n)
    {
        c[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
        f[1] = n % mod;
        for (int i = 2; i <= n; ++i)
        {
            f[i] = (ll)2 * f[i - 1] * (n - 1) % mod;
            for (int j = 1; j <= i - 2; ++j)
                f[i] = (f[i] + (ll)c[i - 1][j] * f[j] % mod * f[i - j - 1] % mod * (n - 2) % mod) % mod;
        }
        return f[n];
    }
};
int main()
{
    SumOverPermutations TC13764;
    int n;
    scanf("%d", &n);
    printf("%d", TC13764.findSum(n));
    return 0;
}