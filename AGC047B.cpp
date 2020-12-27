#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, cnt;
int bo[1000005], sum[1000005];
int tr[1000005][26], num[1000005][26];
ll ans;
char s[1000005];
void dfs(int k, int fa)
{
    if (bo[k])
        for (int i = 0; i < 26; ++i)
            num[k][i] += bo[k];
    for (int i = 0; i < 26; ++i)
        if (tr[k][i])
        {
            dfs(tr[k][i], k);
            sum[k] += sum[tr[k][i]];
            for (int j = 0; j < 26; ++j)
                if (i != j)
                    num[k][j] += num[tr[k][i]][j];
        }
    for (int i = 0; i < 26; ++i)
        if (tr[k][i] && bo[tr[k][i]])
            ans += (ll)bo[tr[k][i]] * (sum[k] - num[k][i] - sum[tr[k][i]] + sum[tr[k][i]] - bo[tr[k][i]]);
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1), rt = 0;
        for (int j = len; j >= 1; --j)
        {
            int k = s[j] - 'a';
            if (!tr[rt][k])
                tr[rt][k] = ++cnt;
            rt = tr[rt][k];
        }
        ++bo[rt];
        ++sum[rt];
    }
    dfs(0, 0);
    printf("%lld", ans);
    return 0;
}