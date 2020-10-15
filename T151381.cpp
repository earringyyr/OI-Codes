#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, head[26], tail[26], nxt[500005], c[500005];
ll k;
char s[500005], ans[500005];
int lowbit(int x)
{
    return x & -x;
}
void add(int x, int val)
{
    while (x <= n)
    {
        c[x] += val;
        x += lowbit(x);
    }
    return;
}
int ask(int x)
{
    int num = 0;
    while (x >= 1)
    {
        num += c[x];
        x -= lowbit(x);
    }
    return num;
}
int main()
{
    scanf("%d%lld", &n, &k);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
    {
        add(i, 1);
        int x = s[i] - 'a';
        if (!head[x])
            head[x] = i;
        else
            nxt[tail[x]] = i;
        tail[x] = i;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 26; ++j)
            if (head[j])
            {
                int num = ask(head[j] - 1);
                if (num <= k)
                {
                    ans[i] = 'a' + j;
                    k -= num;
                    add(head[j], -1);
                    head[j] = nxt[head[j]];
                    break;
                }
            }
    for (int i = 1; i <= n; ++i)
        putchar(ans[i]);
    return 0;
}