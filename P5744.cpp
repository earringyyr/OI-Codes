#include <iostream>
#include <cstdio>
using namespace std;
int n, sai, sco;
string nam;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> nam >> sai >> sco;
        ++sai;
        sco = sco + sco / 5;
        if (sco > 600)
            sco = 600;
        cout << nam << " " << sai << " " << sco << endl;
    }
    return 0;
}