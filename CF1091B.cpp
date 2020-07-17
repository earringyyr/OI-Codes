#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n, a[1005][3], b[1005][3], use[1005];
void dfs(int k, int x, int y)
{
    if (k == n + 1)
    {
        cout << x << " " << y;
        exit(0);
    }
    for (int i = 1; i <= n; ++i)
        if (use[i] == 0 && (k == 1 || (a[k][1] + b[i][1] == x && a[k][2] + b[i][2] == y)))
        {
            use[i] = 1;
            dfs(k + 1, a[k][1] + b[i][1], a[k][2] + b[i][2]);
            use[i] = 0;
        }
    return;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i][1] >> a[i][2];
    for (int i = 1; i <= n; ++i)
        cin >> b[i][1] >> b[i][2];
    dfs(1, 0, 0);
    return 0;
}