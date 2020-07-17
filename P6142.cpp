#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
int n, sum, head[100005], f[100005];
struct node
{
    int v;
    int nxt;
} a[200005];
void ins(int u, int v)
{
    ++sum;
    a[sum].v = v;
    a[sum].nxt = head[u];
    head[u] = sum;
    return;
}
bool dfs(int k, int fa, int val)
{
    multiset<int> s;
    int d = head[k];
    while (d)
    {
        if (a[d].v != fa)
        {
            if (!dfs(a[d].v, k, val))
                return false;
            s.insert(f[a[d].v]);
        }
        d = a[d].nxt;
    }
    int num = 0, p = 0;
    f[k] = 0;
    while (!s.empty())
    {
        multiset<int>::iterator lef, rig;
        lef = s.begin();
        int l = *lef;
        s.erase(lef);
        if (l >= val)
        {
            if (!num)
                f[k] = l;
            continue;
        }
        rig = s.lower_bound(val - l);
        if (rig != s.end())
        {
            if (*rig >= val && !num)
            {
                f[k] = max(f[k], l);
                p = 1;
            }
            s.erase(rig);
        }
        else
        {
            ++num;
            if (num > 1)
                return false;
            f[k] = l;
        }
    }
    if (k == 1 && f[k] != 0 && f[k] < val && !p)
        return false;
    ++f[k];
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ins(x, y);
        ins(y, x);
    }
    int lef = 1, rig = n;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (dfs(1, 0, mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    printf("%d", lef);
    return 0;
}