#include <iostream>
#include <cstdio>
using namespace std;
int n, m, a[50][50], num[50];
int use[50], sum = 0x3f3f3f, ma;
char aa[50][50];
void dfs(int k)
{
    if (k == n + 1)
    {
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            if (num[i] > m - num[i])
                ans += num[i];
            else
                ans += n - num[i];
        if (ans > ma)
            ma = ans;
        if (ans == m * n)
        {
            int len = 0;
            for (int i = 1; i <= n; ++i)
                if (use[i] == 1)
                    len++;
            for (int i = 1; i <= m; ++i)
                if (num[i] < n - num[i])
                    len++;
            if (len < sum)
                sum = len;
        }
        return;
    }
    dfs(k + 1);
    use[k] = 1;
    for (int i = 1; i <= m; ++i)
        if (a[k][i] == 1)
        {
            a[k][i] = 0;
            num[i]++;
        }
        else
        {
            a[k][i] = 1;
            num[i]--;
        }
    dfs(k + 1);
    use[k] = 0;
    for (int i = 1; i <= m; ++i)
        if (a[k][i] == 1)
        {
            a[k][i] = 0;
            num[i]++;
        }
        else
        {
            a[k][i] = 1;
            num[i]--;
        }
    return;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> aa[i][j];
            a[i][j] = aa[i][j] - '0';
            if (a[i][j] == 0)
                num[j]++;
        }
    }
    dfs(1);
    if (ma == m * n)
        cout << sum;
    else
        cout << m * n - ma;
    return 0;
}