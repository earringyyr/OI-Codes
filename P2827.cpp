#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, qq, u, v, t, a[100005];
queue<int> q[3];
bool cmp(int aa, int bb)
{
    return aa > bb;
}
int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &qq, &u, &v, &t);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        q[0].push(a[i]);
    for (int i = 1; i <= m; ++i)
    {
        int ma = -0x7f7f7f7f, id;
        if (!q[0].empty() && q[0].front() > ma)
        {
            ma = q[0].front();
            id = 0;
        }
        if (!q[1].empty() && q[1].front() > ma)
        {
            ma = q[1].front();
            id = 1;
        }
        if (!q[2].empty() && q[2].front() > ma)
        {
            ma = q[2].front();
            id = 2;
        }
        q[id].pop();
        int x = (long long)(ma + i * qq - qq) * u / v;
        int y = (ma + i * qq - qq) - x;
        x -= i * qq;
        y -= i * qq;
        q[1].push(x);
        q[2].push(y);
        if (i % t == 0)
            printf("%d ", ma + i * qq - qq);
    }
    putchar('\n');
    for (int i = 1; i <= m + n; ++i)
    {
        int ma = -0x7f7f7f7f, id;
        if (!q[0].empty() && q[0].front() > ma)
        {
            ma = q[0].front();
            id = 0;
        }
        if (!q[1].empty() && q[1].front() > ma)
        {
            ma = q[1].front();
            id = 1;
        }
        if (!q[2].empty() && q[2].front() > ma)
        {
            ma = q[2].front();
            id = 2;
        }
        q[id].pop();
        if (i % t == 0)
            printf("%d ", ma + m * qq);
    }
    return 0;
}