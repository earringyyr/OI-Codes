#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
int n, m, sx, sy, ex, ey, hh, tt = 1;
int use[26];
int gox[4] = {0, 0, 1, -1}, goy[4] = {1, -1, 0, 0};
int vis[2005][2005], dis[2005][2005];
pii l[4000005];
char s[2005][2005];
vector<pii> vec[26];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (s[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
            else if (s[i][j] == 'G')
            {
                ex = i;
                ey = j;
            }
            else if (s[i][j] >= 'a' && s[i][j] <= 'z')
                vec[s[i][j] - 'a'].push_back(mp(i, j));
        }
    l[1] = mp(sx, sy);
    vis[sx][sy] = 1;
    while (hh < tt)
    {
        pii k = l[++hh];
        for (int i = 0; i < 4; ++i)
        {
            int x = k.first + gox[i], y = k.second + goy[i];
            if (x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y] && s[x][y] != '#')
            {
                vis[x][y] = 1;
                dis[x][y] = dis[k.first][k.second] + 1;
                l[++tt] = mp(x, y);
            }
        }
        if (s[k.first][k.second] >= 'a' && s[k.first][k.second] <= 'z' && !use[s[k.first][k.second] - 'a'])
        {
            int w = s[k.first][k.second] - 'a';
            use[w] = 1;
            int siz = vec[w].size();
            for (int i = 0; i < siz; ++i)
                if (!vis[vec[w][i].first][vec[w][i].second])
                {
                    vis[vec[w][i].first][vec[w][i].second] = 1;
                    dis[vec[w][i].first][vec[w][i].second] = dis[k.first][k.second] + 1;
                    l[++tt] = mp(vec[w][i].first, vec[w][i].second);
                }
        }
    }
    if (!vis[ex][ey])
        printf("-1");
    else
        printf("%d", dis[ex][ey]);
    return 0;
}