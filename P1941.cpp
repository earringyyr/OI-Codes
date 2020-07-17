#include <iostream>
#include <cstdio>
using namespace std;
const int inf = 1000000000;
int n, m, k, x[10005], y[10005];
int l[10005], h[10005], d[10005][1005][2];
int p[10005];
int ans;
struct node
{
    int p;
    int l;
    int h;
} a[10005];
int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];
    for (int i = 0; i <= n; ++i)
    {
        l[i] = 1;
        h[i] = m;
    }
    for (int i = 1; i <= k; ++i)
    {
        cin >> p[i];
        cin >> l[p[i]] >> h[p[i]];
        l[p[i]]++;
        h[p[i]]--;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            d[i][j][0] = inf;
            d[i][j][1] = inf;
        }
    for (int i = 1; i <= m; ++i)
    {
        d[0][i][0] = 0;
        d[0][i][1] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        int pp = 0;
        for (int j = 1; j <= m + x[i - 1]; ++j)
        {
            if (j <= m)
            {
                if (j - x[i - 1] >= l[i - 1] && j - x[i - 1] <= h[i - 1])
                {
                    d[i][j][1] = min(d[i][j][1], d[i - 1][j - x[i - 1]][0] + 1);
                    d[i][j][0] = min(d[i][j][0], d[i][j][1]);
                }
                if (j + y[i - 1] >= l[i - 1] && j + y[i - 1] <= h[i - 1])
                    d[i][j][0] = min(d[i][j][0], d[i - 1][j + y[i - 1]][0]);
                if (j - x[i - 1] > 0)
                {
                    d[i][j][1] = min(d[i][j][1], d[i][j - x[i - 1]][1] + 1);
                    d[i][j][0] = min(d[i][j][0], d[i][j][1]);
                }
                if (j >= l[i] && j <= h[i] && d[i][j][0] != inf)
                    pp = 1;
            }
            else
            {
                if (j - x[i - 1] >= l[i - 1] && j - x[i - 1] <= h[i - 1])
                    d[i][m][0] = min(d[i][m][0], d[i - 1][j - x[i - 1]][0] + 1);
                if (j - x[i - 1] > 0)
                    d[i][m][0] = min(d[i][m][0], d[i][j - x[i - 1]][1] + 1);
                if (m >= l[i] && m <= h[i] && d[i][m][0] != inf)
                    pp = 1;
            }
        }
        if (pp == 0)
        {
            int num = 0;
            for (int j = 1; j <= k; ++j)
                if (p[j] < i)
                    num++;
            cout << 0 << endl;
            cout << num;
            return 0;
        }
    }
    ans = inf;
    for (int i = l[n]; i <= h[n]; ++i)
        if (d[n][i][0] < ans)
            ans = d[n][i][0];
    cout << 1 << endl
         << ans;
    return 0;
}