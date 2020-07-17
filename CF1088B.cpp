#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,cnt=0,top,a[100005];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;)
    {
        cout<<a[i]-top<<endl;
        cnt++;
        if(cnt>=k)
            return 0;
        top+=a[i]-top;
        while(i<=n&&a[i]<=top)
            ++i;
    }
    while(cnt<k)
    {
        cnt++;
        cout<<0<<endl;
    }
    return 0;
}