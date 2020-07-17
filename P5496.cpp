#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int len, cnt, lst;
char s[500005];
struct node
{
    int len;
    int fail;
    int num;
    int son[26];
} tr[500005];
int get_fail(int id, int w)
{
    while (s[w - tr[id].len - 1] != s[w])
        id = tr[id].fail;
    return id;
}
void insert(int k, int w)
{
    int cur = get_fail(lst, w);
    if (!tr[cur].son[k])
    {
        lst = ++cnt;
        tr[cnt].len = tr[cur].len + 2;
        tr[cnt].fail = tr[get_fail(tr[cur].fail, w)].son[k];
        tr[cnt].num = tr[tr[cnt].fail].num + 1;
        tr[cur].son[k] = cnt;
    }
    else
        lst = tr[cur].son[k];
    return;
}
int main()
{
    scanf("%s", s + 1);
    len = strlen(s + 1);
    tr[0].fail = 1;
    tr[1].len = -1;
    tr[1].fail = 1;
    cnt = 1;
    lst = 1;
    for (int i = 1; i <= len; ++i)
    {
        if (i != 1)
            s[i] = (s[i] - 97 + tr[lst].num) % 26 + 97;
        insert(s[i] - 'a', i);
        printf("%d ", tr[lst].num);
    }
    return 0;
}