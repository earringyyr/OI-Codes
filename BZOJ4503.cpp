#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;
bitset<100005> ans, mch[26];
int n, m, num;
char s[100005], t[100005];
int main()
{
    scanf("%s%s", s, t);
    n = strlen(s);
    m = strlen(t);
    for (int i = 0; i < n; ++i)
        mch[s[i] - 'a'][i] = true;
    ans.set();
    for (int i = 0; i < m; ++i)
        if (t[i] != '?')
            ans &= (mch[t[i] - 'a'] >> i);
    for (int i = 0; i < n - m + 1; ++i)
        if (ans[i])
            ++num;
    printf("%d\n", num);
    for (int i = 0; i < n - m + 1; ++i)
        if (ans[i])
            printf("%d\n", i);
    return 0;
}