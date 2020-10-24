#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1000000007;
int sum, num = 1, inv2, vis[50005], pri[50005], f[200005];
void FWT(int *c, int type)
{
    for (int mid = 1; mid < num; mid <<= 1)
        for (int j = 0; j < num; j += (mid << 1))
            for (int k = 0; k < mid; ++k)
            {
                int x = c[j + k], y = c[j + mid + k];
                c[j + k] = (x + y) % mod;
                c[j + mid + k] = (x - y + mod) % mod;
                if (type == -1)
                {
                    c[j + k] = (ll)c[j + k] * inv2 % mod;
                    c[j + mid + k] = (ll)c[j + mid + k] * inv2 % mod;
                }
            }
    return;
}
int ksm(int aa, int k)
{
    int bb = 1;
    while (k)
    {
        if (k & 1)
            bb = (ll)aa * bb % mod;
        aa = (ll)aa * aa % mod;
        k >>= 1;
    }
    return bb;
}
class Nim
{
public:
    int count(int K, int L)
    {
        inv2 = ksm(2, mod - 2);
        for (int i = 2; i <= L; ++i)
        {
            if (!vis[i])
            {
                vis[i] = i;
                pri[++sum] = i;
            }
            for (int j = 1; j <= sum && pri[j] <= vis[i] && i * pri[j] <= L; ++j)
                vis[i * pri[j]] = pri[j];
        }
        for (int i = 1; i <= sum; ++i)
            f[pri[i]] = 1;
        while (num <= 2 * L)
            num <<= 1;
        FWT(f, 1);
        for (int i = 0; i < num; ++i)
            f[i] = ksm(f[i], K);
        FWT(f, -1);
        return f[0];
    }
};
int main()
{
    Nim TC11469;
    int K, L;
    scanf("%d%d", &K, &L);
    printf("%d", TC11469.count(K, L));
    return 0;
}