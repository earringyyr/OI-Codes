#include<iostream>
#include<cstdio>
using namespace std;
int n,k,qwq,ans[26],num;
char a[200005];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=n;++i)
    {
        if(i==1||a[i]==a[i-1])
            qwq++;
        else
            qwq=1;
        if(qwq==k)
        {
            ans[a[i]-'a']++;
            qwq=0;
        }
    }
    for(int i=0;i<26;++i)
        if(ans[i]>num)
            num=ans[i];
    cout<<num;
    return 0;
}