#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int n, m, cnt, ans, a[5005], b[5005], sum[5005], num[5005], v[100005], z[100005];
int gcd(int x, int y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
bool check(int k)
{
    int l = 1, r = m;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (b[mid] > k)
            r = mid - 1;
        else
            l = mid;
    }
    return b[l] == k;
}
void xxs()
{
    for (int i = 2; i <= sqrt(1000000000); ++i)
    {
        if (!v[i])
        {
            v[i] = i;
            z[++cnt] = i;
        }
        for (int j = 1; j <= cnt && z[j] * i <= sqrt(1000000000) && z[j] <= v[i]; ++j)
            v[z[j] * i] = z[j];
    }
    return;
}
int main()
{
    xxs();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if (i == 1)
            sum[i] = a[i];
        else
            sum[i] = gcd(sum[i - 1], a[i]);
    }
    num[n] = 1;
    for (int i = 1; i <= m; ++i)
        scanf("%d", &b[i]);
    for (int i = n; i >= 1; --i)
    {
        int k = a[i], tot = 0;
        for (int j = 1; j <= cnt && z[j] <= sqrt(a[i]); ++j)
            if (k % z[j] == 0)
            {
                int num = 0;
                while (k % z[j] == 0)
                {
                    ++num;
                    k /= z[j];
                }
                if (check(z[j]))
                    ans -= num;
                else
                    ans += num;
            }
        if (k > 1)
        {
            if (check(k))
                --ans;
            else
                ++ans;
        }
        k = sum[i] / num[i];
        for (int j = 1; j <= cnt && z[j] <= sqrt(sum[i] / num[i]); ++j)
            if (k % z[j] == 0)
            {
                int num = 0;
                while (k % z[j] == 0)
                {
                    ++num;
                    k /= z[j];
                }
                if (check(z[j]))
                    tot += num;
                else
                    tot -= num;
            }
        if (k > 1)
        {
            if (check(k))
                ++tot;
            else
                --tot;
        }
        if (tot > 0)
        {
            num[i - 1] = sum[i];
            ans += tot * i;
        }
        else
            num[i - 1] = num[i];
    }
    printf("%d", ans);
    return 0;
}