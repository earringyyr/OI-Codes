#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
using namespace std;
#define inf 1e9
int n, a, b, pos, mod = 1000000;
long long ans;
set<int> s;
int my_abs(int k)
{
    if (k < 0)
        return -k;
    return k;
}
int main()
{
    pos = -1;
    cin >> n;
    s.insert(inf);
    s.insert(-inf);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a >> b;
        if (pos == -1 || pos == a || s.size() <= 2)
        {
            s.insert(b);
            pos = a;
        }
        else
        {
            set<int>::iterator h, t;
            h = --s.lower_bound(b);
            t = s.lower_bound(b);
            if (*h != -inf && my_abs(*h - b) <= my_abs(*t - b))
            {
                ans = (ans + my_abs(*h - b)) % mod;
                s.erase(h);
            }
            else
            {
                ans = (ans + my_abs(*t - b)) % mod;
                s.erase(t);
            }
        }
    }
    cout << ans;
    return 0;
}