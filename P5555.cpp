#include <iostream>
#include <cstdio>
using namespace std;
int n, m, num, ans;
struct pam
{
    int cnt;
    int lst;
    struct tree
    {
        int len;
        int fail;
        int num;
        int son[26];
    } tr[300005];
    char s[300005];
    void init()
    {
        cnt = 1;
        lst = 1;
        tr[0].fail = 1;
        tr[1].len = -1;
        tr[1].fail = 1;
        return;
    }
    int getfail(int id, int w)
    {
        while (s[w - tr[id].len - 1] != s[w])
            id = tr[id].fail;
        return id;
    }
    void ins(int k, int w)
    {
        int cur = getfail(lst, w);
        if (!tr[cur].son[k])
        {
            lst = ++cnt;
            tr[cnt].len = tr[cur].len + 2;
            tr[cnt].fail = tr[getfail(tr[cur].fail, w)].son[k];
            tr[cur].son[k] = cnt;
        }
        else
            lst = tr[cur].son[k];
        return;
    }
} p1, p2;
void dfs(int k1, int k2)
{
    if (p1.tr[k1].len > ans)
    {
        ans = p1.tr[k1].len;
        num = 0;
    }
    if (p1.tr[k1].len == ans)
        ++num;
    for (int i = 0; i < 26; ++i)
        if (p1.tr[k1].son[i] && p2.tr[k2].son[i])
            dfs(p1.tr[k1].son[i], p2.tr[k2].son[i]);
    return;
}
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s%s", p1.s + 1, p2.s + 1);
    p1.init();
    p2.init();
    for (int i = 1; i <= n; ++i)
        p1.ins(p1.s[i] - 'a', i);
    for (int i = 1; i <= m; ++i)
        p2.ins(p2.s[i] - 'a', i);
    dfs(0, 0);
    dfs(1, 1);
    printf("%d %d", ans, num);
    return 0;
}