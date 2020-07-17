#include <iostream>
#include <cstdio>
using namespace std;
int n, m, ans, h[500005], c[500005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= 500000)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int query(int x)
{
    int ans = 0;
    while (x >= 1)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &h[i]);
        if (h[i] > h[i - 1])
        {
            add(h[i - 1] + 1, 1);
            add(h[i] + 1, -1);
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'Q')
        {
            int c;
            scanf("%d", &c);
            c = c ^ ans;
            printf("%d\n", ans = query(c));
        }
        else
        {
            int a, b;
            scanf("%d%d", &a, &b);
            a = a ^ ans;
            b = b ^ ans;
            if (h[a] > h[a - 1])
            {
                add(h[a - 1] + 1, -1);
                add(h[a] + 1, 1);
            }
            if (h[a + 1] > h[a])
            {
                add(h[a] + 1, -1);
                add(h[a + 1] + 1, 1);
            }
            h[a] = b;
            if (h[a] > h[a - 1])
            {
                add(h[a - 1] + 1, 1);
                add(h[a] + 1, -1);
            }
            if (h[a + 1] > h[a])
            {
                add(h[a] + 1, 1);
                add(h[a + 1] + 1, -1);
            }
        }
    }
    return 0;
}