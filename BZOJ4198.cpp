#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
long long n, k, w[1000005];
struct node
{
    long long a;
    long long b;
    bool operator<(const node aa) const
    {
        if (a > aa.a)
            return 1;
        if (a < aa.a)
            return 0;
        if (b > aa.b)
            return 1;
        return 0;
    }
    node(long long aa = 0, long long bb = 0)
    {
        a = aa;
        b = bb;
    }
};
priority_queue<node> s;
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &w[i]);
    long long num = 0;
    for (int j = 1; j <= n; ++j)
        s.push(node(w[j], 0));
    int len = n;
    while ((len - 1) % (k - 1) != 0)
    {
        ++len;
        s.push(node(0, 0));
    }
    while (s.size() > 1)
    {
        long long sum = 0;
        long long ma = 0;
        for (int j = 1; j <= k; ++j)
        {
            sum += s.top().a;
            ma = max(ma, s.top().b);
            s.pop();
        }
        num += sum;
        s.push(node(sum, ma + 1));
    }
    printf("%lld\n%lld", num, s.top().b);
    return 0;
}
