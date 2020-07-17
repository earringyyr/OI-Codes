#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int p = 439847, base = 32984;
int n, m, ans, l, r, cnt, num;
int a[1005], b[100005], vis[500005], use[500005], yly[500005];
char s[15];
int hashs(char *ss)
{
    long long sum = 0;
    int len = strlen(ss);
    for (int i = 0; i < len; ++i)
        sum = (sum * base + ss[i]) % p;
    return sum;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> s;
        a[i] = hashs(s);
        vis[a[i]] = 1;
    }
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> s;
        b[i] = hashs(s);
        if (vis[b[i]] && !use[b[i]])
        {
            use[b[i]] = 1;
            cnt++;
        }
    }
    if (!cnt)
    {
        puts("0\n0");
        return 0;
    }
    cout << cnt << endl;
    l = 1;
    r = 0;
    ans = 1000000000;
    while (r < m)
    {
        ++r;
        if (vis[b[r]] && !yly[b[r]])
            num++;
        yly[b[r]]++;
        while (l <= r && (!vis[b[l]] || yly[b[l]] > 1))
        {
            yly[b[l]]--;
            ++l;
        }
        if (num == cnt)
            ans = min(ans, r - l + 1);
    }
    cout << ans;
    return 0;
}