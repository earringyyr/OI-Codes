#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n, m, c, k, cnt;
int use[75], vis[75];
ull ans = 1;
int readint()
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
ull readull()
{
    ull x = 0;
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
int main()
{
    n = readint();
    m = readint();
    c = readint();
    k = readint();
    for (int i = 1; i <= n; ++i)
    {
        ull a;
        a = readull();
        for (int j = 0; j < k; ++j)
            if ((a >> j) & 1)
                use[j] = 1;
    }
    for (int i = 1; i <= m; ++i)
    {
        int p, q;
        p = readint();
        q = readint();
        if (p >= 0 && p < k)
            vis[p] = 1;
    }
    for (int i = 0; i < k; ++i)
        if (use[i] || !vis[i])
        {
            ++cnt;
            ans <<= 1;
        }
    if (n == 0 && cnt == 64)
    {
        printf("18446744073709551616");
        return 0;
    }
    ans -= n;
    printf("%llu", ans);
    return 0;
}