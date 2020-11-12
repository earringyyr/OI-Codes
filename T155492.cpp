#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <tr1/unordered_map>
using namespace std;
using namespace tr1;
typedef long long ll;
int n;
ll ans;
char s[20];
unordered_map<string, int> mp;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        sort(s, s + len + 1);
        string ss;
        for (int j = 1; j <= len; ++j)
            ss += s[j];
        ans += mp[ss];
        ++mp[ss];
        printf("%lld\n", ans);
    }
    return 0;
}