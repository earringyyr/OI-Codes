#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
int n, lst = 1, cnt = 1, sum;
int num[300005], head[300005];
ll ans;
char s[300005];
struct node
{
    int v;
    int nxt;
} a[300005];
struct tree
{
    int len;
    int fail;
    int num;
    int son[26];
} tr[300005];
int getfail(int id, int w)
{
    while (s[w - tr[id].len - 1] != s[w])
        id = tr[id].fail;
    return id;
}
void insert(int k, int w)
{
    int cur = getfail(lst, w);
    if (!tr[cur].son[k])
    {
        lst = ++cnt;
        tr[cnt].len = tr[cur].len + 2;
        tr[cnt].fail = tr[getfail(tr[cur].fail, w)].son[k];
        tr[cur].son[k] = lst;
    }
    else
        lst = tr[cur].son[k];
    ++tr[lst].num;
}
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
void dfs(int k)
{
    int d = head[k];
    while (d)
    {
        dfs(a[d].v);
        tr[k].num += tr[a[d].v].num;
        d = a[d].nxt;
    }
    ans = max(ans, (ll)tr[k].num * tr[k].len);
    return;
}
int main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    tr[0].fail = 1;
    tr[1].len = -1;
    tr[1].fail = 1;
    for (int i = 1; i <= n; ++i)
        insert(s[i] - 'a', i);
    for (int i = 0; i <= cnt; ++i)
        if (i != 1)
            ins(tr[i].fail, i);
    dfs(1);
    printf("%lld", ans);
    return 0;
}