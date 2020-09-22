#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int maxn, num[26];
char s[10000007];
int main()
{
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; ++i)
        ++num[s[i] - 'a'];
    for (int i = 0; i < 26; ++i)
        maxn = max(maxn, num[i]);
    printf("%d", maxn);
    return 0;
}