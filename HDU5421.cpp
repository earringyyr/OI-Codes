#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, l, r, cnt, lst[2];
long long ans;
char s[200005];
struct node
{
    int len;
    int fail;
    int num;
    int son[26];
} tr[100005];
int get_fail(int id, int w, int type)
{
    if (type == 0)
        while (w + tr[id].len + 1 > r || s[w + tr[id].len + 1] != s[w])
            id = tr[id].fail;
    else
        while (w - tr[id].len - 1 < l || s[w - tr[id].len - 1] != s[w])
            id = tr[id].fail;
    return id;
}
void insert(int k, int w, int type)
{
    int cur = get_fail(lst[type], w, type);
    if (!tr[cur].son[k])
    {
        lst[type] = ++cnt;
        memset(tr[cnt].son, 0, sizeof(tr[cnt].son));
        tr[cnt].len = tr[cur].len + 2;
        tr[cnt].fail = tr[get_fail(tr[cur].fail, w, type)].son[k];
        tr[cnt].num = tr[tr[cnt].fail].num + 1;
        tr[cur].son[k] = cnt;
    }
    else
        lst[type] = tr[cur].son[k];
    ans += tr[lst[type]].num;
    if (tr[lst[type]].len == r - l + 1)
        lst[type ^ 1] = lst[type];
    return;
}
int main()
{
    tr[0].fail = 1;
    tr[1].len = -1;
    tr[1].fail = 1;
    while (scanf("%d", &n) == 1)
    {
        ans = 0;
        cnt = 1;
        lst[0] = 1;
        lst[1] = 1;
        l = 100001;
        r = 100000;
        memset(tr[0].son, 0, sizeof(tr[0].son));
        memset(tr[1].son, 0, sizeof(tr[1].son));
        for (int i = 1; i <= n; ++i)
        {
            int op;
            char ch;
            scanf("%d", &op);
            if (op == 1)
            {
                scanf(" %c", &ch);
                s[--l] = ch;
                insert(ch - 'a', l, 0);
            }
            else if (op == 2)
            {
                scanf(" %c", &ch);
                s[++r] = ch;
                insert(ch - 'a', r, 1);
            }
            else if (op == 3)
                printf("%d\n", cnt - 1);
            else if (op == 4)
                printf("%lld\n", ans);
        }
    }
    return 0;
}