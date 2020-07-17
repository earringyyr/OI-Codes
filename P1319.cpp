#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int a[40001],num,n,k;
int main()
{
    int sum=0,fan=0;
    cin>>n; 
    while(cin>>k)
    {
        for(int i=1;i<=k;++i)
            a[++sum]=fan;
        fan++;
        fan%=2;
        num+=k;
    }
    int len=0;
    for(int i=1;i<=sum;++i)
    {
        cout<<a[i];
        len++;
        if(len==n)
        {
            len=0;
            cout<<endl;
        }
    }
    return 0;
}
