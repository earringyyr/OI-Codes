#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, a[505][505], l[250005][3], use[505][505], head = 0, tail = 1;
int gx[4] = {0, -1, 1, 0}, gy[4] = {1, 0, 0, -1};
int dao[505][505], ans;
struct node
{
    int kai;
    int jie;
} b[505];
bool comp(node aa, node bb)
{
    if (aa.kai < bb.kai)
        return 1;
    if (aa.kai > bb.kai)
        return 0;
    if (aa.jie < bb.jie)
        return 1;
    return 0;
}
void bfs(int xxx, int yyy)
{
    memset(use, 0, sizeof(use));
    l[1][1] = xxx;
    l[1][2] = yyy;
    use[xxx][yyy] = 0;
    head = 0;
    tail = 1;
    while (head < tail)
    {
        head++;
        int x = l[head][1];
        int y = l[head][2];
        if (y == n)
            dao[xxx][x] = 1;
        for (int i = 0; i < 4; ++i)
        {
            int xx = x + gx[i];
            int yy = y + gy[i];
            if (xx >= 1 && xx <= m && yy >= 1 && yy <= n && use[xx][yy] == 0 && a[xx][yy] < a[x][y])
            {
                use[xx][yy] = 1;
                tail++;
                l[tail][1] = xx;
                l[tail][2] = yy;
            }
        }
    }
    return;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[j][i];
    for (int i = 1; i <= m; ++i)
        if (a[i][1] >= a[i - 1][1] && a[i][1] >= a[i + 1][1])
            bfs(i, 1);
    for (int i = 1; i <= m; ++i)
    {
        int p = 0;
        for (int j = 1; j <= m; ++j)
            if (dao[j][i] != 0)
            {
                p = 1;
                break;
            }
        if (p == 0)
            ans++;
    }
    if (ans != 0)
    {
        cout << 0 << endl;
        cout << ans;
        return 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        int kai = -1, jie = -1;
        for (int j = 1; j <= m; ++j)
        {
            if (dao[i][j] == 1 && kai == -1)
                kai = j;
            if (dao[i][j] == 0 && kai != -1)
            {
                jie = j - 1;
                break;
            }
            if (dao[i][j] == 1 && j == m)
                jie = j;
        }
        b[i].kai = kai;
        b[i].jie = jie;
    }
    sort(b + 1, b + m + 1, comp);
    int shi = 1, lin = -1;
    for (int i = 1; i <= m; ++i)
    {
        if (b[i].kai <= shi && (b[i + 1].kai > shi || (i == m && shi != m + 1)))
        {
            ++ans;
            shi = b[i].jie + 1;
        }
        else if (lin != -1 && b[i].kai == b[lin - 1].kai)
            shi = max(shi, b[i].jie + 1);
    }
    cout << 1 << endl;
    cout << ans;
    return 0;
}