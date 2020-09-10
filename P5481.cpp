#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int n, m, k, p, sum, ans = 1, Ans = 1;
int pri[100005], vis[100005], num[100005], a[100005];
int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &p);
    for (register int i = 2; i <= m; ++i)
    {
        if (!vis[i])
        {
            vis[i] = i;
            pri[++sum] = i;
        }
        for (register int j = 1; j <= sum && pri[j] <= vis[i] && i * pri[j] <= m; ++j)
            vis[i * pri[j]] = pri[j];
    }
    for (register int i = 1; i <= sum; ++i)
    {
        int j = m / pri[i];
        while (j)
        {
            num[i] += j;
            j /= pri[i];
        }
    }
    for (register int i = 1; i <= m; ++i)
        a[i] = i + k - 1;
    for (register int i = 1; i <= sum; ++i)
        for (register int j = ((k - 1) / pri[i] + 1) * pri[i]; j <= m + k - 1 && num[i]; j += pri[i])
            while (num[i] && a[j - k + 1] % pri[i] == 0)
            {
                a[j - k + 1] /= pri[i];
                --num[i];
            }
    for (register int i = 1; i <= m; ++i)
        ans = (ll)ans * a[i] % p;
    for (register int i = 0; i < n; ++i)
        Ans = (ll)Ans * (ans - i) % p;
    Ans = ((ll)Ans + p) % p;
    printf("%d", Ans);
    return 0;
}