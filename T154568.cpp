#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
int n;
unordered_map<int, int> mp;
int dfs(int k)
{
    if (k == 0)
        return 0;
    if (mp[k])
        return mp[k];
    int tmp = k;
    if (k % 2 == 0)
        tmp = min(tmp, dfs(k / 2) + 1);
    if (k % 3 == 0)
        tmp = min(tmp, dfs(k / 3) + 1);
    if ((k - 1) % 2 == 0)
        tmp = min(tmp, dfs((k - 1) / 2) + 2);
    if ((k - 1) % 3 == 0)
        tmp = min(tmp, dfs((k - 1) / 3) + 2);
    if ((k - 2) % 3 == 0)
        tmp = min(tmp, dfs((k - 2) / 3) + 3);
    mp[k] = tmp;
    return mp[k];
}
int main()
{
    for (int i = 1; i <= 1000000; ++i)
    {
        mp[i] = mp[i - 1] + 1;
        if (i % 2 == 0)
            mp[i] = min(mp[i], mp[i / 2] + 1);
        if (i % 3 == 0)
            mp[i] = min(mp[i], mp[i / 3] + 1);
    }
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        printf("%d\n", dfs(n));
    }
    return 0;
}