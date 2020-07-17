#include <iostream>
#include <cstdio>
using namespace std;
int n, a[300005], h, t, k, ans;
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    h = 0;
    t = 1;
    k = 0;
    while (h < n && t < n && k < n)
    {
        if (a[(h + k) % n] == a[(t + k) % n])
            ++k;
        else
        {
            if (a[(h + k) % n] < a[(t + k) % n])
                t = t + k + 1;
            if (a[(h + k) % n] > a[(t + k) % n])
                h = h + k + 1;
            if (h == t)
                ++t;
            k = 0;
        }
    }
    ans = min(h, t);
    for (int i = 0; i < n; ++i)
        cout << a[(i + ans) % n] << " ";
    return 0;
}