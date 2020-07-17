#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
#define inf 2000000
int n, ans, a[1000000];
multiset<int> s;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    s.insert(inf);
    s.insert(-inf);
    s.insert(a[1]);
    ans = a[1];
    for (int i = 2; i <= n; ++i)
    {
        multiset<int>::iterator it, l, r;
        it = s.insert(a[i]);
        l = --it;
        ++it;
        r = ++it;
        --it;
        ans += min(a[i] - *l, *r - a[i]);
    }
    cout << ans;
    return 0;
}