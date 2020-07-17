#include <iostream>
#include <cstdio>
using namespace std;
int n, k, ans;
int fa[150005];
int getfather(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = getfather(fa[x]);
    return fa[x];
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= 3 * n; ++i)
        fa[i] = i;
    for (int i = 1; i <= k; ++i)
    {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (x > n || y > n)
        {
            ans++;
            continue;
        }
        if (opt == 1)
        {
            if (getfather(x + n) == getfather(y) || getfather(x) == getfather(y + n))
                ans++;
            else
            {
                fa[getfather(x)] = getfather(y);
                fa[getfather(x + n)] = getfather(y + n);
                fa[getfather(x + 2 * n)] = getfather(y + 2 * n);
            }
        }
        else
        {
            if (getfather(x) == getfather(y) || getfather(x) == getfather(y + n))
                ans++;
            else
            {
                fa[getfather(x + n)] = getfather(y);
                fa[getfather(x + 2 * n)] = getfather(y + n);
                fa[getfather(x)] = getfather(y + 2 * n);
            }
        }
    }
    cout << ans;
    return 0;
}