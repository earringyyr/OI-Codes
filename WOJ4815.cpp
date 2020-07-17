#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, s, l[200005];
long long ans;
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    s = read();
    for (int i = 1; i <= n; ++i)
        l[i] = read();
    sort(l + 1, l + n + 1);
    int head = 1, tail = n;
    while (head < tail)
    {
        while (head < tail && l[head] + l[tail] > s)
            --tail;
        ans += tail - head;
        ++head;
    }
    printf("%lld", ans);
    return 0;
}