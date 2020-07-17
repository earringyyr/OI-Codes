#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, p, num, ren, tail[10], head[10], s[10];
int vis[1005][1005], a[1005][1005], b[1005][1005];
int ans[10], l[10][1000005][2], ju[10][1000005];
int gox[5] = {0, 1, -1, 0, 0}, goy[5] = {0, 0, 0, 1, -1};
int main()
{
    cin >> n >> m >> p;
    for (register int i = 1; i <= p; ++i)
        cin >> s[i];
    for (register int i = 1; i <= n; ++i)
    {
        getchar();
        for (register int j = 1; j <= m; ++j)
        {
            char lin;
            lin = getchar();
            if (lin == '.')
                a[i][j] = 0;
            else if (lin == '#')
            {
                a[i][j] = -1;
                num++;
            }
            else
            {
                a[i][j] = lin - '0';
                ans[a[i][j]]++;
                num++;
                b[i][j]++;
                ++tail[a[i][j]];
                l[a[i][j]][tail[a[i][j]]][0] = i;
                l[a[i][j]][tail[a[i][j]]][1] = j;
            }
        }
    }
    while (1)
    {
        ren++;
        if (ren == p + 1)
            ren = 1;
        if (num == n * m)
            break;
        for (register int i = head[ren]; i <= tail[ren]; ++i)
            ju[ren][i] = 0;
        while (head[ren] < tail[ren])
        {
            head[ren]++;
            if (ju[ren][head[ren]] == s[ren])
            {
                head[ren]--;
                break;
            }
            for (register int fang = 1; fang <= 4; ++fang)
            {
                int xx = l[ren][head[ren]][0] + gox[fang], yy = l[ren][head[ren]][1] + goy[fang];
                if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && a[xx][yy] == 0)
                {
                    a[xx][yy] = ren;
                    ans[ren]++;
                    num++;
                    tail[ren]++;
                    l[ren][tail[ren]][0] = xx;
                    l[ren][tail[ren]][1] = yy;
                    ju[ren][tail[ren]] = ju[ren][head[ren]] + 1;
                }
            }
        }
    }
    for (register int i = 1; i <= p; ++i)
        cout << ans[i] << " ";
    return 0;
}