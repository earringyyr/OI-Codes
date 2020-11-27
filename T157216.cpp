#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, k, m, sum, t;
int a[500005], ans[500005];
int c[20000005];
int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= k)
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
    n = read();
    k = read();
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        sum += a[i];
    }
    if (k <= 2 * sum)
    {
        c[1] = n;
        for (int i = 1; i <= n; ++i)
        {
            int tmp = min(a[i], k);
            c[tmp + 1] -= 1;
            if (a[i] > tmp)
                ans[++m] = a[i] - tmp;
        }
        int num = 0;
        for (int i = 1; i <= k; ++i)
        {
            num += c[i];
            int tmp = min(num, k - i);
            c[i + 1] += 1;
            c[i + tmp + 1] -= 1;
            if (num > tmp)
                ans[++m] = num - tmp;
        }
        sort(ans + 1, ans + m + 1);
        printf("%d\n", m);
        for (int i = m; i >= 1; --i)
            printf("%d ", ans[i]);
    }
    else
    {
        for (int i = 1; i <= sum; ++i)
            if (i * (i + 1) / 2 >= sum)
            {
                t = i;
                break;
            }
        k = (k - 2 * sum) % t;
        c[1] = n;
        for (int i = 1; i <= n; ++i)
        {
            int tmp = min(a[i], 2 * sum);
            c[tmp + 1] -= 1;
            if (a[i] > tmp)
                ans[++m] = a[i] - tmp;
        }
        int num = 0;
        for (int i = 1; i <= 2 * sum; ++i)
        {
            num += c[i];
            int tmp = min(num, 2 * sum - i);
            c[i + 1] += 1;
            c[i + tmp + 1] -= 1;
            if (num > tmp)
                ans[++m] = num - tmp;
        }
        for (int i = 1; i <= m; ++i)
            a[i] = ans[i];
        n = m;
        m = 0;
        memset(c, 0, sizeof(c));
        c[1] = n;
        for (int i = 1; i <= n; ++i)
        {
            int tmp = min(a[i], k);
            c[tmp + 1] -= 1;
            if (a[i] > tmp)
                ans[++m] = a[i] - tmp;
        }
        num = 0;
        for (int i = 1; i <= k; ++i)
        {
            num += c[i];
            int tmp = min(num, k - i);
            c[i + 1] += 1;
            c[i + tmp + 1] -= 1;
            if (num > tmp)
                ans[++m] = num - tmp;
        }
        sort(ans + 1, ans + m + 1);
        printf("%d\n", m);
        for (int i = m; i >= 1; --i)
            printf("%d ", ans[i]);
    }
    return 0;
}