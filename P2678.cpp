#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int l, n, m, lef, rig, d[50005];
bool check(int k)
{
    int cnt = 0, w = 0;
    for (int i = 1; i <= n; ++i)
        if (w + k > d[i])
            ++cnt;
        else
            w = d[i];
    if (w + k > l)
        ++cnt;
    return cnt <= m;
}
int main()
{
    cin >> l >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> d[i];
    sort(d + 1, d + n + 1);
    lef = 1;
    rig = l;
    while (lef < rig)
    {
        int mid = (lef + rig + 1) >> 1;
        if (check(mid))
            lef = mid;
        else
            rig = mid - 1;
    }
    cout << lef;
    return 0;
}