#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        char k = 'a';
        int a;
        while (k < '0' || k > '9')
            k = getchar();
        while (k >= '0' && k <= '9')
        {
            a = k - '0';
            k = getchar();
        }
        if (a % 2 == 0)
            cout << "even" << endl;
        else
            cout << "odd" << endl;
    }
    return 0;
}