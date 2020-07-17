#include <iostream>
#include <cstdio>
using namespace std;
int n, m, s, t, a, w, d[200005];
long long ans;
int read()
{
    int x = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}
int main()
{
    n = read();
    m = read();
    for (int i = 2; i <= m; ++i)
    {
        a = read();
        d[i] = d[i - 1] + a;
    }
    for (int i = 1; i <= n; ++i)
    {
        s = read();
        t = read();
        w = read();
        ans += (d[t] - d[s]) * w;
    }
    printf("%lld", ans);
    return 0;
}