#include <cstdio>
#include <iostream>
using namespace std;
struct node
{
    int a;
    int b;
    int c;
} a[100001];
int guo[100001], tim, l[300001];
int main()
{
    //freopen("port.in","r",stdin);
    //freopen("port.out","w",stdout);
    int n, k, head = 1, top = 0, sum = 0, num = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int len = head;
        cin >> tim >> k;
        while (head <= top && tim - a[head].a >= 86400)
        {
            head++;
        }
        a[++top].a = tim;
        a[top].b = sum + 1;
        a[top].c = sum + k;
        for (int k = len; k < head; k++)
        {
            for (int j = a[k].b; j <= a[k].c; j++)
            {
                guo[l[j]]--;
                if (guo[l[j]] == 0)
                    num--;
            }
        }
        for (int t = 1; t <= k; t++)
        {
            cin >> l[++sum];
            guo[l[sum]]++;
            if (guo[l[sum]] == 1)
                num++;
        }
        cout << num << endl;
    }
    return 0;
}
