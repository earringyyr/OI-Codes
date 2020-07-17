#include <iostream>
#include <cstdio>
using namespace std;
int n, a[1000005], zhong, ans1, ans2, qi = 0x3f3f3f;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int kai, jie;
        cin >> kai >> jie;
        if (jie > zhong)
            zhong = jie;
        if (kai < qi)
            qi = kai;
        for (int j = kai; j < jie; ++j)
            a[j] = 1;
    }
    int num = 1;
    for (int i = qi + 1; i <= zhong; ++i)
    {
        if (a[i] == a[i - 1])
            num++;
        else
        {
            if (i != 1 && a[i] != a[i - 1])
            {
                if (a[i - 1] == 1)
                    ans1 = max(ans1, num);
                else
                    ans2 = max(ans2, num);
                num = 1;
            }
        }
    }
    if (a[zhong - 1] == 1)
        ans1 = max(ans1, num);
    else
        ans2 = max(ans2, num);
    cout << ans1 << " " << ans2;
    return 0;
}