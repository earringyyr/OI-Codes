#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n, base = 2333;
int cnt[26], c[35], f[2][2000005];
ull h[2000005], hsh[2000005];
ll ans;
char s[2000005];
int gethsh(int l, int r)
{
    return hsh[r] - hsh[l - 1] * h[r - l + 1];
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= 27)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ans = 0;
        memset(c, 0, sizeof(c));
        memset(f, 0, sizeof(f));
        scanf("%s", s + 1);
        n = strlen(s + 1);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; ++i)
        {
            f[0][i] = f[0][i - 1];
            ++cnt[s[i] - 'a'];
            if (cnt[s[i] - 'a'] % 2 == 0)
                --f[0][i];
            else
                ++f[0][i];
        }
        memset(cnt, 0, sizeof(cnt));
        for (int i = n; i >= 1; --i)
        {
            f[1][i] = f[1][i + 1];
            ++cnt[s[i] - 'a'];
            if (cnt[s[i] - 'a'] % 2 == 0)
                --f[1][i];
            else
                ++f[1][i];
        }
        h[0] = 1;
        for (int i = 1; i <= n; ++i)
            h[i] = h[i - 1] * base;
        for (int i = 1; i <= n; ++i)
            hsh[i] = hsh[i - 1] * base + s[i] - 'a';
        for (int i = 2; i < n; ++i)
        {
            add(f[0][i - 1] + 1, 1);
            int pos = i, num = 0;
            for (int j = 2 * i; j < n; j += i)
                if (gethsh(1, i) == gethsh(j - i + 1, j))
                {
                    pos = j;
                    ++num;
                }
                else
                    break;
            ans += (ll)ask(f[1][pos + 1] + 1) * (num / 2 + 1);
            if (num > 0)
                ans += (ll)ask(f[1][pos - i + 1] + 1) * ((num + 1) / 2);
        }
        printf("%lld\n", ans);
    }
    return 0;
}