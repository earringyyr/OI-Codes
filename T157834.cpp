#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, q;
int p[500005], c[500005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= n)
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
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);
    for (int i = 2; i < n; ++i)
        if ((p[i] > p[i - 1] && p[i] > p[i + 1]) || (p[i] < p[i - 1] && p[i] < p[i + 1]))
            add(i, 1);
    for (int i = 1; i <= q; ++i)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x > y)
                swap(x, y);
            if (x >= 2 && x < n && y - 1 != x)
                if ((p[x] > p[x - 1] && p[x] > p[x + 1]) || (p[x] < p[x - 1] && p[x] < p[x + 1]))
                    add(x, -1);
            if (x - 1 >= 2 && x - 1 < n)
                if ((p[x - 1] > p[x - 1 - 1] && p[x - 1] > p[x - 1 + 1]) || (p[x - 1] < p[x - 1 - 1] && p[x - 1] < p[x - 1 + 1]))
                    add(x - 1, -1);
            if (x + 1 >= 2 && x + 1 < n)
                if ((p[x + 1] > p[x + 1 - 1] && p[x + 1] > p[x + 1 + 1]) || (p[x + 1] < p[x + 1 - 1] && p[x + 1] < p[x + 1 + 1]))
                    add(x + 1, -1);
            if (y >= 2 && y < n && x + 1 != y)
                if ((p[y] > p[y - 1] && p[y] > p[y + 1]) || (p[y] < p[y - 1] && p[y] < p[y + 1]))
                    add(y, -1);
            if (y - 1 >= 2 && y - 1 < n)
                if ((p[y - 1] > p[y - 1 - 1] && p[y - 1] > p[y - 1 + 1]) || (p[y - 1] < p[y - 1 - 1] && p[y - 1] < p[y - 1 + 1]))
                    add(y - 1, -1);
            if (y + 1 >= 2 && y + 1 < n)
                if ((p[y + 1] > p[y + 1 - 1] && p[y + 1] > p[y + 1 + 1]) || (p[y + 1] < p[y + 1 - 1] && p[y + 1] < p[y + 1 + 1]))
                    add(y + 1, -1);
            swap(p[x], p[y]);
            if (x >= 2 && x < n && y - 1 != x)
                if ((p[x] > p[x - 1] && p[x] > p[x + 1]) || (p[x] < p[x - 1] && p[x] < p[x + 1]))
                    add(x, 1);
            if (x - 1 >= 2 && x - 1 < n)
                if ((p[x - 1] > p[x - 1 - 1] && p[x - 1] > p[x - 1 + 1]) || (p[x - 1] < p[x - 1 - 1] && p[x - 1] < p[x - 1 + 1]))
                    add(x - 1, 1);
            if (x + 1 >= 2 && x + 1 < n)
                if ((p[x + 1] > p[x + 1 - 1] && p[x + 1] > p[x + 1 + 1]) || (p[x + 1] < p[x + 1 - 1] && p[x + 1] < p[x + 1 + 1]))
                    add(x + 1, 1);
            if (y >= 2 && y < n && x + 1 != y)
                if ((p[y] > p[y - 1] && p[y] > p[y + 1]) || (p[y] < p[y - 1] && p[y] < p[y + 1]))
                    add(y, 1);
            if (y - 1 >= 2 && y - 1 < n)
                if ((p[y - 1] > p[y - 1 - 1] && p[y - 1] > p[y - 1 + 1]) || (p[y - 1] < p[y - 1 - 1] && p[y - 1] < p[y - 1 + 1]))
                    add(y - 1, 1);
            if (y + 1 >= 2 && y + 1 < n)
                if ((p[y + 1] > p[y + 1 - 1] && p[y + 1] > p[y + 1 + 1]) || (p[y + 1] < p[y + 1 - 1] && p[y + 1] < p[y + 1 + 1]))
                    add(y + 1, 1);
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            if (l == r)
                puts("1");
            else
                printf("%d\n", ask(r - 1) - ask(l) + 2);
        }
    }
    return 0;
}