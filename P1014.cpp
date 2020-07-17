#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    int n,sum=0,num;
    cin>>n;
    int i;
    for(i=1;sum<n;i++)
        sum+=i;
    num=sum-n;
    if(i%2==0)
    {
        cout<<num+1<<"/"<<i-num-1;
    }
    else
    {
        cout<<i-num-1<<"/"<<num+1;
    }
    return 0; 
}
