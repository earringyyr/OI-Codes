#include <iostream>
using namespace std;
int n, num;
string s;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        num = 0;
        cin >> s;
        if (s.size() == 5)
            cout << "3" << endl;
        else
        {
            if (s[0] != 'o')
                ++num;
            if (s[1] != 'n')
                ++num;
            if (s[2] != 'e')
                ++num;
            if (num <= 1)
                cout << "1" << endl;
            else
                cout << "2" << endl;
        }
    }
    return 0;
}