#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, cnt[26];
string name[100005];
struct node
{
    int id;
    int k;
} a;
node b[26][100005];
bool cmp(node aa, node bb)
{
    if (aa.k != bb.k)
        return aa.k > bb.k;
    return aa.id < bb.id;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        a.id = i;
        cin >> name[i] >> a.k;
        b[name[i][name[i].length() - 1] - 'a'][++cnt[name[i][name[i].length() - 1] - 'a']] = a;
    }
    for (int i = 0; i < 26; ++i)
        sort(b[i] + 1, b[i] + cnt[i] + 1, cmp);
    for (int i = 1; i <= m; ++i)
    {
        char ch;
        int k;
        scanf(" %c%d", &ch, &k);
        if (k > cnt[ch - 'a'])
            puts("Orz YYR tql");
        else
            cout << name[b[ch - 'a'][k].id] << endl;
    }
    return 0;
}