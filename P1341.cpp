#include <iostream>
#include <cstdio>
using namespace std;
int n, w, ww, cnt, top, tot, num[100], vis[100][100], q[5005], fa[5005];
char s[2];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
void dfs(int k)
{
    for (int i = 1; i <= 52; ++i)
        if (vis[k][i])
        {
            --vis[k][i];
            --vis[i][k];
            dfs(i);
        }
    q[++top] = k;
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 52; ++i)
        fa[i] = i;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s);
        int x, y;
        if (s[0] >= 'A' && s[0] <= 'Z')
            x = s[0] - 'A' + 1;
        else
            x = s[0] - 'a' + 27;
        if (s[1] >= 'A' && s[1] <= 'Z')
            y = s[1] - 'A' + 1;
        else
            y = s[1] - 'a' + 27;
        ++num[x];
        ++num[y];
        ++vis[x][y];
        ++vis[y][x];
        if (getfather(x) != getfather(y))
            fa[getfather(x)] = getfather(y);
    }
    for (int i = 1; i <= 52; ++i)
        if (num[i] && fa[i] == i)
            ++tot;
    if (tot > 1)
    {
        printf("No Solution");
        return 0;
    }
    w = -1;
    ww = -1;
    for (int i = 1; i <= 52; ++i)
    {
        if (ww == -1 && num[i])
            ww = i;
        if (num[i] & 1)
        {
            ++cnt;
            if (w == -1)
                w = i;
        }
    }
    if (cnt == 1 || cnt > 2)
    {
        printf("No Solution");
        return 0;
    }
    if (w != -1)
        dfs(w);
    else
        dfs(ww);
    for (int i = top; i >= 1; --i)
        if (q[i] >= 1 && q[i] <= 26)
            putchar(q[i] + 'A' - 1);
        else
            putchar(q[i] + 'a' - 27);
    return 0;
}