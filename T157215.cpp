#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int n, k, lef, rig, maxn, ans;
int a[2005];
multiset<int, greater<int> > s;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        lef = max(lef, a[i]);
        maxn = max(maxn, a[i]);
        rig += a[i];
    }
    while (lef < rig)
    {
        int mid = (lef + rig) >> 1, flg = 0;
        s.clear();
        for (int i = 1; i <= n; ++i)
            s.insert(a[i]);
        for (int i = 1; i <= k; ++i)
        {
            int num = mid;
            while (!s.empty())
            {
                multiset<int, greater<int> >::iterator it = s.lower_bound(num);
                if (it == s.end())
                    break;
                num -= *it;
                s.erase(it);
            }
            if (s.empty())
                break;
        }
        if (s.empty())
            flg = 1;
        if (flg)
            rig = mid;
        else
            lef = mid + 1;
    }
    for (int mid = max(maxn, lef - maxn + 1); mid <= lef; ++mid)
    {
        s.clear();
        for (int i = 1; i <= n; ++i)
            s.insert(a[i]);
        for (int i = 1; i <= k; ++i)
        {
            int num = mid;
            while (!s.empty())
            {
                multiset<int, greater<int> >::iterator it = s.lower_bound(num);
                if (it == s.end())
                    break;
                num -= *it;
                s.erase(it);
            }
            if (s.empty())
                break;
        }
        if (s.empty())
        {
            ans = mid;
            break;
        }
    }
    printf("%d", ans);
    return 0;
}